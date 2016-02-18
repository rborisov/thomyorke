/*
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * ***** END GPL LICENSE BLOCK *****
 *
 * Contributor(s): Jiri Hnidek <jiri.hnidek@tul.cz>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

static int running = 0;
static int delay = 1;
static int counter = 0;
static char pid_file_name[128] = "/home/ruinrobo/streamripperd.pid";
static char *conf_file_name = NULL;
static int pid_fd = -1;
static char *app_name = NULL;

/**
 * \brief Callback function for handling signals.
 * \param	sig	identifier of signal
 */
void handle_signal(int sig)
{
	if(sig == SIGINT) {
		syslog(LOG_DEBUG, "Debug: stopping daemon ...\n");
		/* Unlock and close lockfile */
		if(pid_fd != -1) {
			if (lockf(pid_fd, F_ULOCK, 0) == -1) {
                syslog(LOG_ERR, "Error: Failed to release lock\n");
            }
			close(pid_fd);
		}
		/* Try to delete lockfile */
		if(pid_file_name != NULL) {
			unlink(pid_file_name);
		}
		running = 0;
		/* Reset signal handling to default behavior */
		signal(SIGINT, SIG_DFL);
	} else if(sig == SIGHUP) {
		syslog(LOG_DEBUG, "Debug: reloading daemon config file ...\n");
		//read_conf_file(1);
	} else if(sig == SIGCHLD) {
		syslog(LOG_DEBUG, "Debug: received SIGCHLD signal\n");
	}
}

/**
 * \brief This function will daemonize this app
 */
static void daemonize()
{
	pid_t pid = 0;
	int fd;

	/* Fork off the parent process */
	pid = fork();

	/* An error occurred */
	if(pid < 0) {
		exit(EXIT_FAILURE);
	}

	/* Success: Let the parent terminate */
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* On success: The child process becomes session leader */
	if(setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	/* Ignore signal sent from child to parent process */
	signal(SIGCHLD, SIG_IGN);

	/* Fork off for the second time*/
	pid = fork();

	/* An error occurred */
	if(pid < 0) {
		exit(EXIT_FAILURE);
	}

	/* Success: Let the parent terminate */
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* Set new file permissions */
	umask(0);

	/* Change the working directory to the root directory */
	/* or another appropriated directory */
	if (chdir("/") == -1) {
        syslog(LOG_ERR, "Error: Failed to change directory\n");
    }

	/* Close all open file descriptors */
	for(fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--)
	{
		close(fd);
	}

	/* Reopen stdin (fd = 0), stdout (fd = 1), stderr (fd = 2) */
	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w+");
	stderr = fopen("/dev/null", "w+");

	/* Try to write PID of daemon to lockfile */
	if(pid_file_name != NULL)
	{
		char str[256];
		pid_fd = open(pid_file_name, O_RDWR|O_CREAT, 0640);
		if(pid_fd < 0)
		{
			/* Can't open lockfile */
			exit(EXIT_FAILURE);
		}
		if(lockf(pid_fd, F_TLOCK, 0) < 0)
		{
			/* Can't lock file */
			exit(EXIT_FAILURE);
		}
		/* Get current PID */
		sprintf(str, "%d\n", getpid());
		/* Write PID to lockfile */
		if (write(pid_fd, str, strlen(str)) == -1) {
            syslog(LOG_ERR, "Error: Failed to Write PID to lockfile\n");
        }
	}
}

/**
 * \brief Print help for this application
 */
void print_help(void)
{
	printf("\n Usage: %s [OPTIONS]\n\n", app_name);
	printf("  Options:\n");
	printf("   -h --help                 Print this help\n");
	printf("   -c --conf_file filename   Read configuration from the file\n");
	printf("   -d --daemon               Daemonize this application\n");
	printf("   -p --pid_file  filename   PID file used by daemonized app\n");
	printf("\n");
}

/* Main function */
int main(int argc, char *argv[])
{
	static struct option long_options[] = {
		{"conf_file", required_argument, 0, 'c'},
		{"help", no_argument, 0, 'h'},
		{"daemon", no_argument, 0, 'd'},
		{NULL, 0, 0, 0}
	};
	int value, option_index = 0, ret;
	int start_daemonized = 0;

	app_name = argv[0];

	/* Try to process all command line arguments */
	while( (value = getopt_long(argc, argv, "c:l:t:p:dh", long_options, &option_index)) != -1) {
		switch(value) {
			case 'c':
				conf_file_name = strdup(optarg);
				break;
			case 'd':
				start_daemonized = 1;
				break;
			case 'h':
				print_help();
				return EXIT_SUCCESS;
			case '?':
				print_help();
				return EXIT_FAILURE;
			default:
				break;
		}
	}

	/* When daemonizing is requested at command line. */
	if(start_daemonized == 1) {
		/* It is also possible to use glibc function deamon()
		 * at this point, but it is useful to customize your daemon. */
		daemonize();
	}

	/* Open system log and write message to it */
//    setlogmask(LOG_ERR|LOG_INFO);
    openlog(argv[0], LOG_PID|LOG_CONS, LOG_DAEMON);
	syslog(LOG_INFO, "Started %s", app_name);

	/* Daemon will handle two signals */
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);

	/* This global variable can be changed in function handling signal */
	running = 1;

	/* Never ending loop of server */
	while(running == 1) {
		/* Debug print */
		syslog(LOG_ERR, "Debug: %d\n", counter++);

		/* TODO: dome something useful here */

		/* Real server should use select() or poll() for waiting at
		 * asynchronous event. Note: sleep() is interrupted, when
		 * signal is received. */
		sleep(delay);
	}

	/* Write system log and close it. */
	syslog(LOG_INFO, "Stopped %s", app_name);
    closelog();

	/* Free allocated memory */
	if(conf_file_name != NULL) free(conf_file_name);

	return EXIT_SUCCESS;
}

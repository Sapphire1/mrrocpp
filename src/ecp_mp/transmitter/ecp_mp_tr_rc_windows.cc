// -------------------------------------------------------------------------
// Proces: 	EFFECTOR CONTROL PROCESS (lib::ECP)
// Plik:			ecp_mp_sensor.h
// System:	QNX/MRROC++  v. 6.3
// Opis:		Definicja konstruktora bazowej klasy czujnikow po stronie procesu ECP - jeden dla wszystkich.
// Autor:		yoyek/tkornuta
// Data:		10.11.2005
// -------------------------------------------------------------------------

#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "lib/typedefs.h"
#include "lib/impconst.h"
#include "lib/com_buf.h"				// numery bledow
#include "ecp_mp/transmitter/transmitter.h"
#include "ecp_mp/task/ecp_mp_task.h"
#include "lib/srlib.h"					// klasy bledow
#include "ecp_mp/transmitter/ecp_mp_tr_rc_windows.h"

namespace mrrocpp {
namespace ecp_mp {
namespace transmitter {

rc_win_buf_typedef *rc_windows::rc_win_buf = NULL;

rc_windows::rc_windows  (
		TRANSMITTER_ENUM _transmitter_name,
		const char* _section_name,
		task::task& _ecp_mp_object)  :
			transmitter (_transmitter_name, _section_name, _ecp_mp_object) {

	if(!rc_win_buf) {
		rc_win_buf = new rc_win_buf_typedef;
	} else {
		printf ("powolano juz obiekt klasy transmitter\n");
	}

	sem_init(&(rc_win_buf->sem), 0, 1);

	rc_win_buf->solver_hostname = _ecp_mp_object.config.return_string_value("solver_hostname", _section_name).c_str();
	rc_win_buf->solver_port = _ecp_mp_object.config.return_int_value("solver_port", _section_name);
}


rc_windows::~rc_windows  (){
	sem_destroy(&(rc_win_buf->sem));
	delete[] rc_win_buf->solver_hostname;
	delete rc_win_buf;
}


void * rc_windows::do_query(void * arg) {

  sem_wait(&(rc_win_buf->sem));

  int sock;
  fd_set fds;
  struct timeval timeout;
  int retval;


  /*
  	switch (to_va.rc_windows.rc_state[i]) {
  		case 'Y':
  		case 'y':
  			pattern[i] = 'y'; break;
  		case 'W':
  		case 'w':
  			pattern[i] = 'w'; break;
  		case 'R':
  		case 'r':
  			pattern[i] = 'r'; break;
  		case 'O':
  		case 'o':
  			pattern[i] = 'o'; break;
  		case 'B':
  		case 'b':
  			pattern[i] = 'b'; break;
  		case 'G':
  		case 'g':
  			pattern[i] = 'g'; break;
  	}
  */

  sock = make_socket(rc_win_buf->solver_hostname, rc_win_buf->solver_port);

//  int l = strlen(rc_win_buf->request);
  if (write(sock, rc_win_buf->request, strlen(rc_win_buf->request)) != (ssize_t) strlen(rc_win_buf->request)) {
    perror("write()");
    close(sock);
    return NULL;
  }


  /* Initialize the file descriptor set. */
  FD_ZERO (&fds);
  FD_SET (sock, &fds);

  /* Initialize the timeout data structure. */
  timeout.tv_sec = 60*2;
  timeout.tv_usec = 0;

  /* `select' returns 0 if timeout, 1 if input available, -1 if error. */
  retval = select (FD_SETSIZE, &fds, NULL, NULL, &timeout);
  if (retval == -1) {
	perror("select()");
	close(sock);
	return NULL;
  } else if (retval == 0) {
	fprintf(stderr, "socket timeout\n");
	close(sock);
	return NULL;
  }

  retval = read(sock, rc_win_buf->response, 1024);
  if (retval < 0) {
	perror("read()");
	close(sock);
	return NULL;
  }

  rc_win_buf->response[retval] = '\0';

  printf("%s", rc_win_buf->response);

  close(sock);
  sem_post(&(rc_win_buf->sem));

  return NULL;
}


int rc_windows::make_socket (const char *hostname, uint16_t port)
{
  int sock;
  struct sockaddr_in server;
  struct hostent *hostinfo;

  /* Create the socket. */
  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror ("socket");
    return -1;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons (port);
  hostinfo = gethostbyname (hostname);
  if (hostinfo == NULL) {
    fprintf (stderr, "Unknown host %s.\n", hostname);
    return -1;
  }
  server.sin_addr = *(struct in_addr *) hostinfo->h_addr;

  if(connect(sock, (struct sockaddr*) &server, sizeof(server)) == -1) {
    perror("connect");
    return -1;
  }

  return sock;
}

bool rc_windows::t_write() {

	snprintf(rc_win_buf->request, sizeof(rc_win_buf->request), "GET /?%s HTTP/1.0\r\n", to_va.rc_windows.rc_state);

	pthread_create(&worker, NULL, do_query, NULL);

	return true;
}

bool rc_windows::t_read(bool wait) {

	int l=0;

	if (wait) {
		sem_wait(&(rc_win_buf->sem));

		printf("W SEMAFORZE 1 %d\n", strlen(rc_win_buf->response)-33);

		l=strlen(rc_win_buf->response)-33-16;
		if(l<0) l=0;

		strncpy(from_va.rc_windows.sequence, rc_win_buf->response+33, l);
		from_va.rc_windows.sequence[l]='\0';

		sem_post(&(rc_win_buf->sem));

		return true;
	} else {
		if (sem_trywait(&(rc_win_buf->sem)) == 0) {

			printf("W SEMAFORZE2 %d\n", strlen(rc_win_buf->response)-33);
			l=strlen(rc_win_buf->response)-33-16;
			if(l<0) l=0;
			strncpy(from_va.rc_windows.sequence, rc_win_buf->response+33, l);
			from_va.rc_windows.sequence[l]='\0';

			sem_post(&(rc_win_buf->sem));

			return true;
		} else {
			return false;
		}
	}
}

} // namespace transmitter
} // namespace ecp_mp
} // namespace mrrocpp

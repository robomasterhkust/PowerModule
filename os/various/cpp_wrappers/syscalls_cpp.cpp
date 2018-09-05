/*******************************************************************************
 *    This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/
#include <stdio.h>
#include <errno.h>

#include "osal.h"

#include "syscalls_cpp.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void _exit(int status){
   (void) status;
   osalSysHalt("Unrealized");
   while(TRUE){}
}

pid_t _getpid(void){
   return 1;
}

#undef errno
extern int errno;
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

void _open_r(void){
  return;
}

void __cxa_pure_virtual() {
  osalSysHalt("Pure virtual function call.");
}

#ifdef __cplusplus
}
#endif

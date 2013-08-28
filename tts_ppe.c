#include <stdio.h>
#include <libspe2.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


//Creates the Thread for executing Processes
void *ppu_pthread_function(void *arg) {
  spe_context_ptr_t context = *(spe_context_ptr_t *) arg;
  unsigned int entry = SPE_DEFAULT_ENTRY;
  spe_context_run(context,&entry,0,NULL,NULL,NULL);
  pthread_exit(NULL);
}


//Checks the existence of Files to ascertain the number of threads to be created.
int file_exist (char *filename)
{
 struct stat   buffer;   
 return (stat (filename, &buffer) == 0);
}

extern spe_program_handle_t tts_spe;

int main(void) {

struct timeval tv1, tv2;
	time_t curtime;

  spe_context_ptr_t context[8];
  pthread_t pthread[8];
  unsigned int i;

int a = file_exist("outputa.txt");
int b = file_exist("outputb.txt");
int c = file_exist("outputc.txt");
int d = file_exist("outputd.txt");
int e = file_exist("outpute.txt");
int f = file_exist("outputf.txt");		
int sum = a+b+c+d+e+f;


gettimeofday(&tv1, 0);


  for (i=0;i<sum;i++) {
    context[i] = spe_context_create(0,NULL);
    spe_program_load(context[i],&tts_spe);
    pthread_create(&pthread[i],NULL,&ppu_pthread_function,&context[i]);
  }


  // write SPU ids using mailboxes
  for (i=0;i<sum;i++)
    if (spe_in_mbox_write(context[i],&i,1,SPE_MBOX_ANY_NONBLOCKING) == 0)
      printf("Message could not be written\n");

  for (i=0;i<sum;i++) {
    pthread_join(pthread[i],NULL);
    spe_context_destroy(context[i]);
  }

  //To gain Performance Measure
FILE *filep;
filep=fopen("time.txt","a+");

gettimeofday(&tv2, 0);
long elapsed = (tv2.tv_usec-tv1.tv_usec);

fprintf(filep,"%ld \n",elapsed);

fclose(filep);

a = file_exist("/root/Desktop/tts/DB/spea.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/spea.sh");
system("/root/Desktop/tts/DB/spea.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outputa.wav");
system("rm /root/Desktop/tts/DB/spea.sh");
system("rm /root/Desktop/tts/outputa.wav");
system("rm /root/Desktop/tts/spea.txt");
system("rm /root/Desktop/tts/outputa.txt");
}
a = file_exist("/root/Desktop/tts/DB/speb.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/speb.sh");
system("/root/Desktop/tts/DB/speb.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outputb.wav");
system("rm /root/Desktop/tts/DB/speb.sh");
system("rm /root/Desktop/tts/outputb.wav");
system("rm /root/Desktop/tts/speb.txt");
system("rm /root/Desktop/tts/outputb.txt");
}
a = file_exist("/root/Desktop/tts/DB/spec.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/spec.sh");
system("/root/Desktop/tts/DB/spec.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outputc.wav");
system("rm /root/Desktop/tts/DB/spec.sh");
system("rm /root/Desktop/tts/outputc.wav");
system("rm /root/Desktop/tts/spec.txt");

}
a = file_exist("/root/Desktop/tts/DB/sped.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/sped.sh");
system("/root/Desktop/tts/DB/sped.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outputd.wav");
system("rm /root/Desktop/tts/DB/sped.sh");
system("rm /root/Desktop/tts/outputd.wav");
system("rm /root/Desktop/tts/sped.txt");
}
a = file_exist("/root/Desktop/tts/DB/spee.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/spee.sh");
system("/root/Desktop/tts/DB/spee.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outpute.wav");
system("rm /root/Desktop/tts/DB/spee.sh");
system("rm /root/Desktop/tts/outpute.wav");
system("rm /root/Desktop/tts/spee.txt");
}
a = file_exist("/root/Desktop/tts/DB/spef.sh");
if(a==1){
system("chmod 777 /root/Desktop/tts/DB/spef.sh");
system("/root/Desktop/tts/DB/spef.sh");
system("aplay -c 1 -t wav -q /root/Desktop/tts/outputf.wav");
system("rm /root/Desktop/tts/DB/spef.sh");
system("rm /root/Desktop/tts/outputf.wav");
system("rm /root/Desktop/tts/spef.txt");
}
  return 0;
} 

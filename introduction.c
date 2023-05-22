#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>

#include <sys/stat.h>

void print_introduction() {
  char * skip_intro_file = "data/config/skip_intro";
  if (access(skip_intro_file, F_OK) == 0) {
	  return;
  }


  char * projectname = "ERGOTYPE";
  printf("\n\n\t\t %s\n\n", projectname);
  printf(" (always press enter to continue)\n\n");
  getchar();
  printf("Welcome to %s, which is an typing trainer. \n\n"
	" %s is born out of the idea that the keyboard is an instrument, \n"
	" in the sense of how musical intruments are intruments. \n" 
	" A keyboard is a tool which by the intended userbase is used \n"
	" to an extent that makes a time consuming exercise in mastering\n" 
	" ones own usage of it worthwhile. Just as cellists and violinist\n"
	" master their tool to feel comfortable in any position, \n"
	" playing any node with any (reasonable) finger, the aim of %s is to \n"
	" enable a similar mastery of our tool of choice: the keyboard.\n"
	" \n", "ERGOTYPE", "ERGOTYPE", "ERGOTYPE");
  getchar();
  printf(
	" Regardless of whether you are new to what commonly is kown as\n"
	" touch typing or already an expierienced practitioner, I believe \n"
	" this program might be of value to you.\n"
	" \n");
  getchar();
  printf(
	" For expierienced typist, we might start of slow. For absolute \n"
	" beginners, even the first exercises might seem too hard (I disagree). \n\n");
  getchar();
  printf(
	" To these absolute beginners it might be said that most expiriences \n"
	" typist will suffer almost similarly, likely relearning how to \n"
	" approach typing. At least after a couple of exercises. \n"
	" The expirienced programmer on the other hand shall be warned.\n"
	" The difficulty is rising sharply and furthermore, rougly\n"
	" based on your recent past performance. You may easily find\n"
	" yourself in a position where you are not able to even type a\n"
	" singel word correctly. I advise not to rush.\n"
	" \n "
	);
  getchar();
  printf(
	" Absolute beginners that are frustrated with these exercises \n"
	" are advised to turn to different typing exercise programs first.\n"
	" And return at wish. Other programs will much more likely \n"
	" enable fast progress at the beginning. \n"
	" \n");
  getchar();
  printf(
	" Experienced typists, on the other hand, which are frustrated\n"
	" with these exercises are advised to re-evaluate whether the \n"
	" mastery of the keyboard as aimed for by these exercises is \n"
	" indeed their goal. Exercises using dictionary words appear\n"
	" only after a long time. Many experienced typist frustrated\n"
	" with these exercises most likely are frustrated by their\n"
	" own performance.\n"
	" \n");
  getchar();
  printf(
	" As a final note, as this program is still in alpha, many \n"
	" many essential things are missing. I will comment on them \n"
	" and on the difficulties to realize them along the way. \n"
	" I highly appreciate some help. You will find extensive \n"
	" remarks in the source code of where help is needed. \n"
	" Also, I am open to new ideas. If no agreement can be \n"
	" made, I am also open to forks of this project. But in \n"
	" case you fork this project, please stay in touch as \n"
	" collobaration most likely will benefit everybody.\n");
 getchar();
 while (true) {
 	printf(" Do you want to skip the introduction in the future? (y/n)\n");
	char answer = getchar();
	if (answer != 'y' && answer != 'n') {
		printf("Please press either 'y' or 'n'.\n");
		continue;
	} else {
		if ( answer == 'y' ) {
			FILE * indicator_file = fopen(skip_intro_file,"w");
			if (indicator_file == NULL) {
				perror(NULL);
				exit(1);
			}

			fclose(indicator_file);
		}
		break;
	}
        	
 }
 printf("\n\n\n\n\n");  

}
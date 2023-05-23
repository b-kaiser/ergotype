#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#include <time.h>

#include <errno.h>

#include "homerows.h"
#include "skillset.h"
#include "train.h"

#include "output.h"


static void sig_handler(int _)
{
    (void)_;
    restore_terminal();
    exit(EXIT_SUCCESS);

}

int main() {
  // https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
  srand(time(NULL));
  struct sigaction act;
  act.sa_handler = sig_handler;
  sigaction(SIGINT, &act, NULL);

  init_terminal();


  skillset right_hand = empty_skillset;
  right_hand.hand = right;
  skillset left_hand = empty_skillset; 
  left_hand.hand = left;
  skillset * hands[2] = {&right_hand, &left_hand};

  add_homerow(&right_hand);
  add_homerow(&left_hand);
  while (true) {
    int random_hand = rand() % 2;
    int other_hand = 1 - random_hand;
    skillset * first_hand = hands[random_hand];
    skillset * second_hand = hands[other_hand];

    bool new_latitude = false;
    while ( ! new_latitude ) {
      train(first_hand);
      new_latitude = add_homerow(first_hand);
    }
    new_latitude = false;
    while ( ! new_latitude ) {
      train(second_hand);
      new_latitude = add_homerow(second_hand);
    }

  }

  //printf("Congratulations! You achieved mastery.\n");
 
  restore_terminal(); 
  return EXIT_SUCCESS;
}

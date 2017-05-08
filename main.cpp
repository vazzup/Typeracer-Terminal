#include <iostream>
#include <string>
#include <ncurses.h>
#include <algorithm>
#include <ctime>

#define UNTOUCHED 1
#define CORRECT 2
#define INCORRECT 3

/**************************
 * TODO: Add ability to crawl web for texts
 * TODO: Add versus mode
 * TODO: Add Graphics
 **************************/

int main(int argc, char **argv) {
	initscr();	//Compulsory; Initialize "screen"
	// use CBreak or Raw
	// CBreak states to not ignore CTRL + C and other system interrupts
	// RAW doesnt consider them as interrupts
	raw();
	noecho();	// So that whatever getch() takes isn't echoed onto the screen
	start_color();	// Start color mode
	std::string s = "This is Vatsal's Typeracing Terminal Game.\nYep, it's awesome.";	//String to be typed
	int word_count = 0;
	int len=s.size(), c;
	int correct_index = -1, current_index = -1;
	bool no_errors = true;
	// Count number of words in sentence.
	// Counted under assumption that sentence is properly formatted
	// Each space accounts for one word, 
	// One is added for the final word which isn't followed by a space
	for(int i=0; i<len; i++) {
		if(s[i] == ' ' || s[i] == '\n') {
			word_count++;
		}
	}
	word_count++;
	time_t start, end;
	double exec_time;
	// Color Definitions for the three states possible for each character
	// UNTOUCHED - Haven't reached there yet.
	// CORRECT - The string until this character has been typed correct
	// INCORRECT - The string until this character has some error
	init_pair(UNTOUCHED, COLOR_YELLOW, COLOR_BLACK);
	init_pair(CORRECT, COLOR_GREEN, COLOR_BLACK);
	init_pair(INCORRECT, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(UNTOUCHED) | A_STANDOUT);
	printw(s.c_str());	// Print String initially
	attroff(COLOR_PAIR(UNTOUCHED) | A_STANDOUT);
	ungetch(getch());
	time(&start);
	while((c=getch())) {	//Take inputs constantly
		attron(A_STANDOUT);	// Turn on STANDOUT attribute since all test is highlighted
		move(0, 0);	// Move cursor back to 0, 0
		if(c == 127) {	// Weirdly, getch returns 127 for backspace
			// If backspace encountered
			current_index = std::max(--current_index, -1);
			correct_index = std::min(current_index, correct_index);
		} else {
			// if any other character encountered
			current_index++;
			if(s[current_index] == c && no_errors) {
				correct_index++;
			} else if (s[current_index] != c) {
				no_errors = false;
			}
		}
		// Print correct part of string
		attron(COLOR_PAIR(CORRECT) | A_UNDERLINE);
		for(int i=0; i<=correct_index; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(CORRECT));
		// Print Incorrect part of string
		attron(COLOR_PAIR(INCORRECT));
		for(int i=correct_index + 1; i<=current_index; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(INCORRECT) | A_UNDERLINE);
		// Print rest of string
		attron(COLOR_PAIR(UNTOUCHED));
		for(int i=current_index + 1; i < len; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(UNTOUCHED) | A_STANDOUT);
		if(correct_index == len - 1) {
			// Full string hass been printed correctly
			break;
		}
		if(correct_index == current_index) {
			// All errors have been eradicated by backspace or otherwise
			no_errors = true;
		}
	}
	time(&end);
	exec_time = difftime(end, start);
	addch('\n');
	printw("Congratulations! The execution time is %lf and the speed is %d wpm", exec_time, ((int)(word_count*(60/exec_time))));
	getch();
	endwin();	// Compulsory; Close window
	return 0;
}

#include <iostream>
#include <string>
#include <ncurses.h>
#include <algorithm>

#define UNTOUCHED_PAIR 1
#define CORRECT_PAIR 2
#define INCORRECT_PAIR 3

/**************************
 * TODO: Add timer
 * TODO: Add wpm counter
 * TODO: Add ability ro crawl web for texts
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
	int len=s.size(), c;
	int correct_index = -1, current_index = -1;
	bool no_errors = true;
	// Color Definitions for the three states possible for each character
	// UNTOUCHED - Haven't reached there yet.
	// CORRECT - The string until this character has been typed correct
	// INCORRECT - The string until this character has some error
	init_pair(UNTOUCHED_PAIR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(CORRECT_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(INCORRECT_PAIR, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1) | A_STANDOUT);
	printw(s.c_str());	// Print String initially
	attroff(COLOR_PAIR(1) | A_STANDOUT);
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
		attron(COLOR_PAIR(2) | A_UNDERLINE);
		for(int i=0; i<=correct_index; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(2));
		// Print Incorrect part of string
		attron(COLOR_PAIR(3));
		for(int i=correct_index + 1; i<=current_index; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(3) | A_UNDERLINE);
		// Print rest of string
		attron(COLOR_PAIR(1));
		for(int i=current_index + 1; i < len; i++) {
			addch(s[i]);
		}
		attroff(COLOR_PAIR(1) | A_STANDOUT);
		if(correct_index == len - 1) {
			// Full string hass been printed correctly
			break;
		}
		if(correct_index == current_index) {
			// All errors have been eradicated by backspace or otherwise
			no_errors = true;
		}
	}
	addch('\n');
	printw("Congratulations!");
	getch();
	endwin();	// Compulsory; Close window
	return 0;
}

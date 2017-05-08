import curses
import time

def main():
	stdscr = curses.initscr()
	curses.noecho()
	curses.cbreak()
	stdscr.keypad(True)
	curses.start_color()
	UNTOUCH, CORRECT, INCORRECT = 1, 2, 3
	curses.init_pair(UNTOUCH, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(CORRECT, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(INCORRECT, curses.COLOR_RED, curses.COLOR_BLACK)
	question = "abcdefg"
	correct_index, current_index =  -1, -1
	no_errors = True 

	stdscr.attron(curses.color_pair(UNTOUCH) | curses.A_STANDOUT)
	stdscr.addstr(question)
	stdscr.attroff(curses.color_pair(UNTOUCH))
	curses.ungetch(stdscr.getch())
	start = time.time()
	while True:
		c = stdscr.getch()
		stdscr.move(0, 0)
		if c == curses.KEY_BACKSPACE:
			current_index = max(current_index - 1, -1)
			correct_index - min(current_index, correct_index)
		else:
			current_index += 1
			if question[current_index] == chr(c) and no_errors:
				correct_index += 1
			elif question[current_index] != chr(c):
				no_errors = False
		stdscr.attron(curses.color_pair(CORRECT) | curses.A_UNDERLINE)
		stdscr.addstr(question[ : correct_index + 1])
		stdscr.attroff(curses.color_pair(CORRECT))
		stdscr.attron(curses.color_pair(INCORRECT))
		stdscr.addstr(question[max(correct_index + 1, 0) : current_index + 1])
		stdscr.attroff(curses.color_pair(INCORRECT) | curses.A_UNDERLINE)
		stdscr.attron(curses.color_pair(UNTOUCH))
		stdscr.addstr(question[max(current_index + 1, 0) : ])
		stdscr.attroff(curses.color_pair(UNTOUCH))
		if correct_index == len(question) - 1:
			break
		if correct_index == current_index:
			no_errors = True

	end = time.time()
	stdscr.addstr("Congratulations! Execution Time is " + str(round((end - start), 3)))
	stdscr.addstr("Press any key to continue...")
	stdscr.getch()
	curses.endwin()

if __name__ == '__main__':
	main()


#include <iostream>
#include <Windows.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


static void sigHandler(int sig) {

	exit(0);
}



class ProgressBar {
public:
	double neededProgress;
	int timesRan;
	void update(double newProgress) {
		currentProgress += newProgress;
		amountOfFiller = (int)((currentProgress / neededProgress) * (double)ProgressBarLength);
		this->print();
	}
	string firstPartOfProgressBar = "[",
		lastPartOfProgressBar = "]",
		ProgressBarFiller = "|",
		ProgressBarUpdater = "/-\\|";

	void print() {
		currUpdateVal %= ProgressBarUpdater.length();

		cout << "\r"
			<< firstPartOfProgressBar;

		for (int a = 0; a < amountOfFiller; a++) {
			cout << ProgressBarFiller;
		}

		cout << ProgressBarUpdater[currUpdateVal];


		for (int b = 0; b < ProgressBarLength - amountOfFiller; b++) {
			cout << " ";
		}

		cout << lastPartOfProgressBar
			<< " (" << (int)(100 * (currentProgress / neededProgress)) << "%)"
			<< " Brewed Coffee " << timesRan << " times!  "
			<< flush;
		currUpdateVal += 1;

	}

private:
	int amountOfFiller,
		ProgressBarLength = 50,
		currUpdateVal = 0;
	double currentProgress = 0;


};

static void ToggleNumLock() {
	byte bScan = 0x45;

	keybd_event(VK_NUMLOCK, bScan, KEYEVENTF_EXTENDEDKEY | 0, 0); // Key-down
	keybd_event(VK_NUMLOCK, bScan, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // Key-Up
}

int main() {

	string Dev = "Ambushfall";


	signal(SIGINT, sigHandler);
#ifdef SIGBREAK
	signal(SIGBREAK, sigHandler);
#endif
	signal(SIGABRT, sigHandler);
	signal(SIGTERM, sigHandler);

	cout << "Coffee Brewer " << "Made with <3 by " << Dev << endl;
	cout << "Brewing Coffee..." << endl << endl;
	cout << "Press Ctrl+C to exit..." << endl << endl;

	int TimesRan = 0;

	while (true) {

		ProgressBar bar;
		 int Progress = 35 * 100;
		// int Progress = 10;
		bar.neededProgress = Progress;
		bar.timesRan = TimesRan;
		for (int i = 0; i < Progress; i++) {
			bar.update(1);
			Sleep(1);

		}
		ToggleNumLock();
		TimesRan += 1;
	}
	return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h> 
#include <stdlib.h>


void mode_raw(int activer) {
	static struct termios cooked;
	static int raw_actif = 0;
	if (raw_actif == activer) {return;}
	if (activer) {
		struct termios raw;
		tcgetattr(STDIN_FILENO, &cooked);
		raw = cooked;
		cfmakeraw(&raw);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
	else {tcsetattr(STDIN_FILENO, TCSANOW, &cooked);}
	raw_actif = activer;
}

char ReadKey(void) {
	char c;
	mode_raw(1);
	c = getchar();
	mode_raw(0);
	return c;
}

class test {
	public:
	test() {
		pthread_create(&ptid, NULL, run, this);
		pthread_join(ptid, NULL);
	}

	static void* run(void* arg) {
		while (1)
		{
			usleep(1000000);
			printf("%s\n", "func2");
		} 
	}
	private:
		pthread_t ptid;
};

void* readInputThread(void* arg) {
	while(1) {
		char input = ReadKey();
		if(input == 'p') {
			printf("%s\n", "func1");
		} 
		else if(input == 'r') {
			test t;
		}
	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, readInputThread, NULL);
	pthread_join(thread_id,NULL);

	return 0;
}
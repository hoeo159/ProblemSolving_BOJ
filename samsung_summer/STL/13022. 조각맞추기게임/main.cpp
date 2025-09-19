#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#define BAR_LEN 5

#define CMD_INIT 100
#define CMD_MAKEWALL 200
#define CMD_MATCHPIECE 300

extern void init();
extern void makeWall(int mHeights[BAR_LEN]);
extern int matchPiece(int mHeights[BAR_LEN]);
extern void printInfo(int mHeights[BAR_LEN]);

static bool run()
{
	int N;
	int cmd;
	int heights[BAR_LEN];

	int ret = 0;
	int ans = 0;
	scanf("%d", &N);

	scanf("%d", &cmd);
	bool okay = false;
	if (cmd == CMD_INIT)
	{
		init();
		okay = true;
	}

	for (int turn = 0; turn < N-1; turn++)
	{
		scanf("%d", &cmd);
		for (int i = 0; i < BAR_LEN; i++)
		{
			scanf("%d", &heights[i]);
		}

		switch (cmd)
		{
		case CMD_MAKEWALL:
			makeWall(heights);
			break;
		case CMD_MATCHPIECE:
            // printInfo(heights);
			ret = matchPiece(heights);
			scanf("%d", &ans);
			if (ans != ret)
            {
                // printf("Turn %d : Wrong Answer! Expected %d but got %d\n", turn + 1, ans, ret);
				okay = false;
                exit(0);
            }
            else
            {
                // printf("Turn %d : Correct Answer! Matched at position %d\n", turn + 1, ret);
            }
			break;
		}
	}
	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}
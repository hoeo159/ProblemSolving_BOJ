#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

extern void init(int N);
extern void createGroup(int groupID, int mNum, int uIDs[]);
extern int sendMessage(int uID, int groupID, char text[]);
extern void setOnOff(int uID, int groupID);
extern int checkMsg(int uID, char msg[]);

/////////////////////////////////////////////////////////////////////////

#define INIT	0
#define CREATE	1
#define SEND	2
#define SET		3
#define CHECK	4

static int mSeed;
static int pseudo_rand()
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7fff;
}

static int sample_1;
static int createUids[1000];
static bool run()
{
	int N, cmd, ans, ret;
	int gid, uid, ucnt, len;
	char msg[10], text[10];

	int Q = 0;
	bool okay = false;

	scanf("%d", &Q);
	for (int q = 0; q < Q; ++q)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			scanf("%d %d", &N, &mSeed);
			init(N);
			okay = true;
			break;

		case CREATE:
			scanf("%d %d", &gid, &ucnt);
			for (int m = 0; m < ucnt; m++) {
				scanf("%d", &createUids[m]);
			}
			createGroup(gid, ucnt, createUids);
			break;

		case SEND:
			if (sample_1 == 1) {
				scanf("%d %d %s %d", &uid, &gid, text, &ans);
			}
			else {
				scanf("%d %d %d", &uid, &gid, &ans);
				len = 3 + pseudo_rand() % 7;
				for (int i = 0; i < len; i++) {
					text[i] = 'a' + pseudo_rand() % 26;
				}
				text[len] = 0;
			}
			ret = sendMessage(uid, gid, text);
			if (ans != ret) {
				okay = false;
			}
			break;

		case SET:
			scanf("%d %d", &uid, &gid);
			setOnOff(uid, gid);
			break;

		case CHECK:
			scanf("%d %d %s", &uid, &ans, text);
			ret = checkMsg(uid, msg);
			if (ans != ret || (ans != 0 && strcmp(text, msg) != 0)) {
				okay = false;
			}
			break;

		default:
			okay = false;
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
		if (tc == 1) sample_1 = 1;
		else sample_1 = 0;
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
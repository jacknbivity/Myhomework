#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
struct playerHistory
{
	char playerName[21];//人物名字
	char rank[7];//等级
	char equipmentName[21];//装备命名
	int exp;//经验
	int time;//游戏时间
};
struct skill {//人物技能
	char skillName[21];//技能名
	int hurtValue;//造成的伤害
	int blueDeplete;//耗蓝
	int ID;//技能序号
	int token;//判断技能是否创建
};
struct equipment {//装备
	char equipmentName[21];//装备命名
	int fightValue;//攻击加成
	int blueValue;
	int token;
};
struct player {
	char playerName[21];//人物名字
	char rank[7];//等级
	int time;//游戏时间
	int blood;//血量
	int blue;//蓝
	int fightPlayer;//攻击力
	int money;//灵石
	int exp;//经验
	struct skill playerSkill[7];
	struct equipment playerEquipment;
};
struct monster {
	char monsterName[10];//怪物名
	char monsterRank[10];//怪物境界
	int monsterBlood;//血量
	int monsterfight;//攻击力
	int exp;//经验
	int token; //判断是否为BOSS
	char word[100];//台词
	struct monster* next; //链接下一个节点
};
int ret=1,pass=0;
struct playerHistory tmp[20];
const char backgroundWord[7][1000] = {"此山常有灵气环绕，山内蕴藏少量低阶灵宝.同时，滋生了诸多炼气期的妖魔异兽，更有妖魔首领坐镇于此.所以，此处是练气期修士除魔卫道的大好历练之所。",
									  "曾为飞升仙人的洞府.修真者为求机遇福缘，常常入洞历练探索，福祸相依.更有妖修魔兽潜匿在洞内不时伤人，啖血吸精以促进修为.",
									  "修真宗门天师道的山门所在.龙虎山历来是妖魔异兽藏龙卧虎之地.天师道老祖开山立派之际，就曾豪言修大道者当立于危墙，诛邪魅正贤良.",
									  "规模最大商贸峡谷.因对于人类修真者提升太大，深受妖魔等异族忌惮.终在异族联手的阴谋围剿中，沦为废墟，如今墟内遍布妖兽.",
									  "修真者姬云跨境诛杀大妖柳白之洞.相传柳白在入洞伏诛前似乎心有所感，曾九次心生不安惊疑不定而踟躇不前.故后人讥笑之，戏称此洞为九疑.",
									  "曾经的修行圣地.自水神共工怒触不周山后，灵脉破损，灵宝凋零，渐无人问津.千百年来，不周山灵脉有自愈之势.这才引来各族修真者寻宝历练.传说此处有剑灵.",
									  "上古魔神蚩尤头颅埋葬之地.经年日久，头颅幻化为精纯的灵气，充斥着常羊山。现为修真者的飞升圣地.无奈资源有限，修真者难免会产生摩擦."
};
const char firstpassFile[] = "./dataBase/1.csv";///////////////////
const char secondpassFile[] = "./dataBase/2.csv";  //
const char thirdlypassFile[] = "./dataBase/3.csv"; //
const char fourthpassFile[] = "./dataBase/4.csv";  //保存的数据文件路径
const char fifthpassFile[] = "./dataBase/5.csv";   //
const char SixthpassFile[] = "./dataBase/6.csv";   //
const char SeventhpassFile[] = "./dataBase/7.csv"; //
const char playerHistoryfile[] = "./dataBase/playerRank.csv";/////////////////
struct player createPlayer();//角色属性初始化
void printData(struct player* player);//展示人物属性
int printStart(int userChoice);//输出开始页面
FILE* openFileroot(const char *linkPass,char *a);//文件打开and校验
struct monster *passData(const char *linkData);//怪物数据加载
void passDataLoad(int* pass, struct player* player);//各关卡战斗的主函数
void passPrintdata(struct player* player);//打印角色战斗面板
void passMonsterdata(struct monster* monster);//打印怪物战斗面板
int selectAfter();//用户战后选择
void mainUp(struct player* player, int a, int b, int c,char *rankName);//角色属性提升函数
void playerUp(struct player* player);//对应境界提升函数
void printBackgroundword(const char(*backgroundWord)[1000],int pass);//打印背景函数
void skillCreate(char* name, int* a, int* b, int* c,int f);//自定义功法名函数
void equipmentCreat(char* name, int* a, int* b, int* c, int f);//自定义装备名函数
void fprintfPlayer(struct player* player, const char* linkData);//向文件写入角色数据
void battleCourse(struct player* player, struct monster* monster, int a, int b,const char *linkData);//主要战斗方式函数，回合制
void firstPass(struct player* player);//关卡函数
void secondPass(struct player* player);//
void thirdPass(struct player* player);//
void fourthPass(struct player* player);//
void fifthPass(struct player* player);//
void sixthPass(struct player* player);//
void seventhPass(struct player* player);//关卡函数
void quickSort(struct playerHistory q[], int l, int r);//快速排序
void mergeSort(struct playerHistory q[], int l, int r);//归并排序
void playerHistory(const char* linkData);//打印历史战绩
void hideCursor(int a);//光标隐藏函数
int main()
{
	while (1) {
		int userChoice;
		struct monster* passMonster = NULL;
		struct player player;
		printf("\t\t\t\t\t|**********************************************************************|\n");
		printf("\t\t\t\t\t|*                      欢迎来到文字修仙(简化版)                      *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|*                            1、开始游戏                             *|\n");
		printf("\t\t\t\t\t|*                            2、历史排行                             *|\n");
		printf("\t\t\t\t\t|*                            3、退出游戏                             *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|*                                                                    *|\n");
		printf("\t\t\t\t\t|**********************************************************************|\n");
		printf("\t\t\t\t\t|*所以，你的选择是？");
		ret = scanf_s("%d", &userChoice);
		while ( ret != 1||(userChoice > 3 || userChoice < 1) )
		{
			while (getchar() != '\n');
			printf("\t\t\t\t\t|*道友别乱数入！！！○( ＾皿＾)っHiahiahia…\n");//校验输入
			printf("\t\t\t\t\t|*所以，道友你的选择是？");
			ret = scanf_s("%d", &userChoice);
		}
		switch (userChoice)
		{
		case 1:
			player = createPlayer();
			printData(&player);
			printf("\t\t\t\t\t|*                     道友开始冒险吧                    *|\n");
			while (true)
			{
				userChoice = printStart(userChoice);
				switch (userChoice)
				{
				case 1:
					passDataLoad(&pass, &player);
					system("cls");
					break;
				case 2:
					printData(&player);
					break;
				case 3:
					printf("\n\t\t\t\t\t 已退出");
					exit(0);
				}
			}
			break;
		case 2:
			playerHistory(playerHistoryfile);
			break;
		case 3:
			exit(0);
			break;
		}
	}
	return 0;
}
struct player createPlayer()
{	//角色属性初始化
	int ret=1;
	system("cls");
	struct player player{};
	printf("\n\n\n\n");
	printf("\t\t\t\t\t|*设置你的名字(20个字符内)：");
	ret= scanf_s("%s", player.playerName, 20);
	while (ret!=1 ||strlen(player.playerName) > 20)
	{
		system("cls");
		while (getchar() != '\n');
		printf("\n\n\n\n");
		printf("\t\t\t\t\t|*道友别乱数入！○( ＾皿＾)っHiahiahia…   \t\t\t\t*|\n");
		printf("\t\t\t\t\t|*设置你的道号(20个字符内)：");
		ret = scanf_s("%s", player.playerName, 20);
	}
	srand((unsigned)time(NULL));
	player.blood = rand() % 20 + 10;
	player.blue= rand() % 20 + 10;
	player.fightPlayer = rand() % 7 + 5;
	player.money = 100;
	player.exp = 0;
	strcpy_s(player.rank, 7,"练气期");
	player.time = 0;
	strcpy_s(player.playerSkill[0].skillName, 9,"普通攻击");
	player.playerSkill[0].blueDeplete = 0;
	player.playerSkill[0].token = 1;
	player.playerSkill[0].ID = 0;
	player.playerSkill[0].hurtValue = 0;
	for (int i = 1; i < 7; i++)
	{   //技能初始化
		player.playerSkill[i].token = 0;
		player.playerSkill[i].ID = i;
	}
	player.playerEquipment.token = 0;
	player.playerEquipment.fightValue = 0;
	player.playerEquipment.blueValue = 0;
	return player;
}
void printData(struct player* player)
{   //打印角色基础面板
	system("cls");
	printf("\t\t\t\t\t|*********************************************************|\n");
	printf("\t\t\t\t\t|*————————————————————————————|\n");
	printf("\t\t\t\t\t|*                      角色基础面板                     *|\n");
	printf("\t\t\t\t\t|*————————————————————————————|\n");
	printf("\t\t\t\t\t|*角色名：%-8s\t境界：%s             \t *|\n", player->playerName,player->rank);
	printf("\t\t\t\t\t|*————————————————————————————|\n");
	printf("\t\t\t\t\t|*HP：%-6d\tMP：%-6d\t攻击力：%-4d             *|\n", player->blood, player->blue, player->fightPlayer);
	printf("\t\t\t\t\t|*————————————————————————————|\n");
	printf("\t\t\t\t\t|*灵石：%-10d\tEXP：%-5d                       *|\n", player->money, player->exp);
	printf("\t\t\t\t\t|*————————————————————————————|\n");
	printf("\t\t\t\t\t|*********************************************************|\n");
}
int printStart(int userChoice)
{   //用户选择
	printf("\t\t\t\t\t|*********************************************************|\n");
	printf("\t\t\t\t\t|*1、历练             2、查看面板             3、退出游戏*|\n");
	printf("\t\t\t\t\t|*所以，道友你的选择是？");
	ret = scanf_s("%d", &userChoice);
	while (  ret != 1|| (userChoice > 3 || userChoice < 1))
	{
		while (getchar() != '\n');
		printf("\t\t\t\t\t|*道友别乱数入！！！○( ＾皿＾)っHiahiahia…\n");
		printf("\t\t\t\t\t|*所以，道友你的选择是？");
		ret = scanf_s("%d", &userChoice);
	}
	return userChoice;
}
FILE* openFileroot(const char *linkPass,char * a)
{//以读的方式打开数据文件
	FILE* fileP;
	if (fopen_s(&fileP, linkPass, a ))//校验文件是否可打开
	{
		printf("无法打开此文件\n");            //如果打不开，就输出打不开
		exit(0);                               //终止程序
	}
	if (fileP == NULL) {
		printf("Failed to open the file!\n");
		printf("Please check it."); 
		exit(0);
	}
	return fileP;
}
struct monster* passData(const char* linkData)
{   //向文件读取怪物数据
	struct monster* passMonster = NULL,*pr=NULL,*head=NULL;
	char a[2] = "r";
	FILE* fpassData = openFileroot(linkData,a);
	char move[200],*mid=NULL,*mid2=NULL;
	fscanf_s(fpassData, "%[^\n]", move,200);
	while (!feof(fpassData)){
		passMonster = (struct monster*)malloc(sizeof(struct monster));
		if (passMonster == NULL)
		{
			printf("\t\t\t\t\t 节点申请失败！");
			free(passMonster);
			exit(0);
		}
		fscanf_s(fpassData, "%s\n", move,200);
		mid = strtok_s(move, ",",&mid2);  //使用strtok_s函数以","为分隔符
		for (int i = 0; mid; i++)
		{
			if (i == 0)
				strcpy_s(passMonster->monsterName,strlen(mid)+1, mid);
			if (i == 1)
				strcpy_s(passMonster->monsterRank, strlen(mid)+1, mid);
			if (i == 2)
				passMonster->monsterBlood = atoi(mid);
			if (i == 3)
				passMonster->monsterfight = atoi(mid);
			if (i == 4)
				passMonster->exp = atoi(mid);
			if (i == 5)
				passMonster->token = atoi(mid);
			if (i == 6)
				strcpy_s(passMonster->word, strlen(mid)+1, mid);
			mid = strtok_s(NULL, ",",&mid2);
		}
		if (head == NULL)
		{
			head = passMonster;
			pr = passMonster;
		}
		else
		{
			pr->next = passMonster;
			pr = passMonster;
		}
		passMonster->next = NULL;
	}
	fclose(fpassData);
	return head;
}
void passDataLoad(int* pass, struct player* player)
{	//各关卡战斗的主函数
	int userChoice;
	if (*pass == 0)
	{	//第一关
		system("cls");
		printf("\t\t\t\t\t 君若山\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		firstPass(player);
		playerUp(player);
		*pass+=1;
		printf("\t\t\t\t\t %s：这就是妖兽吗，不过如此。\n\n",player->playerName);
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 1)
	{	//第二关
		system("cls");
		printf("\t\t\t\t\t 稽山洞\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		secondPass(player);
		playerUp(player);
		*pass += 1;
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 2)
	{	//第三关
		system("cls");
		printf("\t\t\t\t\t 龙虎山\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		thirdPass(player);
		playerUp(player);
		*pass += 1;
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 3)
	{	//第四关
		system("cls");
		printf("\t\t\t\t\t 商谷墟\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		fourthPass(player);
		playerUp(player);
		*pass += 1;
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 4)
	{	//第五关
		system("cls");
		printf("\t\t\t\t\t 九疑洞\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		fifthPass(player);
		playerUp(player);
		*pass += 1;
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 5)
	{	//第六关
		system("cls");
		printf("\t\t\t\t\t 不周山\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		sixthPass(player);
		playerUp(player);
		*pass += 1;
		userChoice = selectAfter();
		if (userChoice == 2)
			return;
	}
	if (*pass == 6)
	{	//第七关
		system("cls");
		printf("\t\t\t\t\t 常羊山\n");
		Sleep(700);
		printBackgroundword(backgroundWord, *pass);
		seventhPass(player);
		playerUp(player);
		*pass += 1;
		fprintfPlayer(player, playerHistoryfile);
		printf("\t\t\t\t\t 通关，游戏结束");

	}
}
void passPrintdata(struct player* player)
{	//打印角色战斗面板
	printf("\t\t\t\t\t|*角色名：%-15s\t境界：%-15s    *|\n", player->playerName, player->rank);
	if (player->playerEquipment.token)
		printf("\t\t\t\t\t 武器：%-20s 伤害： %-20d\n", player->playerEquipment.equipmentName,player->playerEquipment.fightValue);
	for (int i = 0; i < 7; i++)
	{//打印可使用的技能
		if (player->playerSkill[i].token == 1) {
			printf("\t\t\t\t\t|*技能序号：%d\t%-13s伤害：%-9dMP:%-10d*|\n", player->playerSkill[i].ID, player->playerSkill[i].skillName, player->playerSkill[i].hurtValue + player->fightPlayer, player->playerSkill[i].blueDeplete);
		}
	}
	printf("\t\t\t\t\t 开始战斗 \t\t\t\t\t\n");
}
void passMonsterdata(struct monster* monster)
{//打印怪物战斗面板
	printf("\t\t\t\t\t 敌人\n");
	printf("\t\t\t\t\t|*%-30s%-25s*|\n", monster->monsterName, monster->monsterRank);
	printf("\t\t\t\t\t %-55s\n", monster->word);
}
int selectAfter()
{//用户战后选择
	int userChoice;
	printf("\t\t\t\t\t 你现在是要\n");
	printf("\t\t\t\t\t|*1、继续历练               2、返回城镇\t");
	ret = scanf_s("%d", &userChoice);
	while (ret != 1 || (userChoice > 2 || userChoice < 1))
	{
		while (getchar() != '\n');
		printf("\t\t\t\t\t|*道友别乱数入！！！○( ＾皿＾)っHiahiahia…\n");
		printf("\t\t\t\t\t|*所以，道友你的选择是？");
		ret = scanf_s("%d", &userChoice);
	}
	return userChoice;
}
void mainUp(struct player* player, int a, int b, int c, char* rankName)
{   //角色属性提升函数
	strcpy_s(player->rank, 7, rankName);
	player->blood *= a;
	player->blue *= b;
	player->fightPlayer *= c;
	printf("\t\t\t\t\t\t\t境界提升\n");
	skillCreate(player->playerSkill[1].skillName, &player->playerSkill[1].hurtValue, &player->playerSkill[1].token, &player->playerSkill[1].blueDeplete, player->fightPlayer);
}
void playerUp(struct player* player)
{   //对应境界提升
	if (player->exp >= 20&& strcmp(player->rank,"练气期")==0)
	{
		char rankName[7] = "筑基期";
		mainUp(player, 3, 2, 2, rankName);
	}
	if (player->exp >= 150 && strcmp(player->rank, "筑基期") == 0)
	{
		char rankName[7] = "结丹期";
		mainUp(player, 3, 2, 2, rankName);
	}
	if (player->exp >= 1000 && strcmp(player->rank, "结丹期") == 0)
	{
		char rankName[7] = "元婴期";
		mainUp(player, 8, 3, 3, rankName);
	}
	if (player->exp >= 5000 && strcmp(player->rank, "元婴期") == 0)
	{
		char rankName[7] = "化神期";
		mainUp(player, 4, 3, 5, rankName);
	}
	if (player->exp >= 20000 && strcmp(player->rank, "化神期") == 0)
	{
		char rankName[7] = "合体期";
		mainUp(player, 7, 3, 2, rankName);
	}
	if (player->exp >= 100000 && strcmp(player->rank, "合体期") == 0)
	{
		char rankName[7] = "大乘期";
		mainUp(player, 7, 3, 4, rankName);
	}
}
void printBackgroundword(const char (* backgroundWord)[1000], int pass)
{//打印背景函数
	printf("\t\t\t\t\t ");
	hideCursor(0);
	for (int i = 0; backgroundWord[pass][i] != '\0'; i++)
	{
		printf("%c", backgroundWord[pass][i]);
		Sleep(30);
		if (backgroundWord[pass][i]=='.')
		{
			printf("\n");
			printf("\t\t\t\t\t ");
		}
	}
	printf("\n");
	hideCursor(1);
}
void skillCreate(char* name, int* a, int* b, int* c,int f)
{   //自定义功法函数
	printf("\t\t\t\t\t|*境界提升悟得一功法\n");
	printf("\t\t\t\t\t|*设置功法名(20个字符内)：");
	ret = scanf_s("%s", name, 20);
	while (ret != 1 || strlen(name) > 20)
	{
		system("cls");
		while (getchar() != '\n');
		printf("\n\n\n\n");
		printf("\t\t\t\t\t|*道友别乱数入！○( ＾皿＾)っHiahiahia…   \t\t\t\t*|\n");
		printf("\t\t\t\t\t|*设置功法名(20个字符内)：");
		ret = scanf_s("%s", name, 20);
	}
	*b = 1;
	*a = int(f * 0.15);
	*c = rand() % 10 + 1;
}
void equipmentCreat(char* name, int* a, int* b, int* c, int f)
{
	printf("\t\t\t\t\t|*击败剑灵获得法宝\n");
	printf("\t\t\t\t\t|*设置法宝名(20个字符内)：");
	ret = scanf_s("%s", name, 20);
	while (ret != 1 || strlen(name) > 20)
	{
		system("cls");
		while (getchar() != '\n');
		printf("\n\n\n\n");
		printf("\t\t\t\t\t|*道友别乱数入！○( ＾皿＾)っHiahiahia…   \t\t\t\t*|\n");
		printf("\t\t\t\t\t|*设置法宝名(20个字符内)：");
		ret = scanf_s("%s", name, 20);
	}
	*a = int(f * 0.15);
	*b = 1;
	*c = rand() % 10 + 1;
}
void fprintfPlayer(struct player* player,const char *linkData)
{   //本次游戏结束后向历史文件中写入角色信息
	char a[2] = "a";
	FILE *filep = openFileroot(linkData, a);
	fprintf(filep, "\n%s,%s,%d,%d",player->playerName,player->rank,player->exp,player->time);
	fclose(filep);
}
void battleCourse(struct player* player,struct monster *monster,int a ,int b,const char * linkData)
{   //主要战斗方式函数，回合制
	int skillOrder = 0;
	struct player temp = *player;
	int randomInt= rand() % 3 + 1;
	while (monster)
	{
		passMonsterdata(monster);
		while (monster->monsterBlood > 0)
		{
			printf("\t\t\t\t\t|*选择你的技能\t");
			ret = scanf_s("%d", &skillOrder);
			while (ret != 1 || temp.playerSkill[skillOrder].token == 0 || skillOrder >= 7 || (temp.blue - temp.playerSkill[skillOrder].blueDeplete) < 0) {
				while (getchar() != '\n');
				printf("\n\t\t\t\t\t|*重新选择你的技能(输入不合法或MP不足)\t");
				ret = scanf_s("%d", &skillOrder);
			}
			monster->monsterBlood -= (temp.fightPlayer + temp.playerEquipment.fightValue + temp.playerSkill[skillOrder].hurtValue);
			temp.blue -= temp.playerSkill[skillOrder].hurtValue;
			if (monster->monsterBlood > 0)
				printf("\t\t\t\t\t|*敌方血量剩余：%d\n", monster->monsterBlood);
			if (monster->monsterBlood <= 0)
			{
				printf("\t\t\t\t\t 你击杀了 %s \n\n", monster->monsterName);
				if (monster->next == NULL)
					Sleep(3000);
				player->money += rand() % a + b;
				player->exp += (player->money)/20;
				player->money = 0;
				player->exp += monster->exp+randomInt;
				break;
			}
			printf("\t\t\t\t\t 向你发起攻击造成 %d点 伤害\n", monster->monsterfight + randomInt);
			temp.blood -= monster->monsterfight + randomInt;
			player->time += 1;
			if (temp.blood < 0)
			{
				fprintfPlayer(player, linkData);
				printf("\t\t\t\t\t 游戏结束！");
				
				exit(0);
			}
		}
		temp = *player;
		monster = monster->next;
	}
}
void firstPass(struct player* player)
{
	struct monster* monster = passData(firstpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 100, 50, playerHistoryfile);
}
void secondPass(struct player* player)
{
	struct monster* monster = passData(secondpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 500, 200, playerHistoryfile);
}
void thirdPass(struct player* player)
{
	struct monster* monster = passData(thirdlypassFile);
	passPrintdata(player);
	battleCourse(player, monster, 2000, 1000, playerHistoryfile);
}
void fourthPass(struct player* player)
{
	struct monster* monster = passData(fourthpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 5000, 2000, playerHistoryfile);
}
void fifthPass(struct player* player)
{
	struct monster* monster = passData(fifthpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 10000, 50000, playerHistoryfile);
}
void sixthPass(struct player* player)
{
	struct monster* monster = passData(SixthpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 20000, 1000, playerHistoryfile);
	srand((unsigned)time(NULL));
	if ((rand() % 2 + 1) == 1)
		equipmentCreat(player->playerEquipment.equipmentName, &player->playerEquipment.fightValue, &player->playerEquipment.token, &player->playerEquipment.blueValue, player->fightPlayer);
}
void seventhPass(struct player* player)
{
	struct monster* monster = passData(SeventhpassFile);
	passPrintdata(player);
	battleCourse(player, monster, 30000, 20000, playerHistoryfile);
}
void quickSort(struct playerHistory q[], int l, int r)
{	//快速排序 逆
	if (l >= r) return;
	int x = q[l].exp, i = l - 1, j = r + 1;
	struct playerHistory temp;
	while (i < j)
	{
		do i++; while (q[i].exp < x);
		do j--; while (q[j].exp > x);
		if (i < j)
		{
			temp = q[i];
			q[i] = q[j];
			q[j] = temp;
		}
	}
	quickSort(q, l, j);
	quickSort(q, j + 1, r);
};
void mergeSort(struct playerHistory q[], int l, int r)
{//归并排序
	if (l >= r) return;
	int mid = l + r >> 1;
	mergeSort(q, l, mid);
	mergeSort(q, mid + 1, r);
	int k = 0, i = l, j = mid + 1;
	while (i <= mid && j <= r)
		if (q[i].exp >= q[j].exp)tmp[k++] = q[i++];
		else tmp[k++] = q[j++];
	while (i <= mid) tmp[k++] = q[i++];
	while (j <= r) tmp[k++] = q[j++];
	for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
}
void playerHistory(const char* linkData)
{   //打印历史战绩
	system("cls");
	struct playerHistory player[20]{};
	for (int i = 0; i < 20; i ++ ) player[i].exp = 0;
	char a[2] = "r";
	FILE* fplayerData = openFileroot(linkData,a);
	char move[200], * mid = NULL, * mid2 = NULL;
	fscanf_s(fplayerData, "%[^\n]", move, 200);
	mid = strtok_s(move, ",", &mid2);
	for(int k=0;!feof(fplayerData);k++)
	{
		fscanf_s(fplayerData, "%s\n", move, 200);
		mid = strtok_s(move, ",", &mid2);
		for (int i = 0; mid; i++)
		{
			if (i == 0)
				strcpy_s(player[k].playerName, strlen(mid) + 1, mid);
			if (i == 1)
				strcpy_s(player[k].rank, strlen(mid) + 1, mid);
			if (i == 2)
				player[k].exp = atoi(mid);
			if (i == 3)
				player[k].time = atoi(mid);
			mid = strtok_s(NULL, ",", &mid2);
		}
	}
	int indx=0, userChoice;
	for (int i = 0; i < 20; i++)
		if (player[i].exp != 0)
			indx ++;
	printf("\t\t\t\t\t 选择查看方式(1.顺序\t2.逆序)：");
	ret = scanf_s("%d", &userChoice);
	while (ret != 1 || (userChoice > 2 || userChoice < 1))
	{
		while (getchar() != '\n');
		printf("\t\t\t\t\t|*道友别乱数入！！！○( ＾皿＾)っHiahiahia…\n");
		printf("\t\t\t\t\t 选择查看方式(1.顺序\t2.逆序)：");
		ret = scanf_s("%d", &userChoice);
	}
	if (userChoice == 1)
		mergeSort(player, 0, indx - 1);
	else 
		quickSort(player, 0, indx - 1);
	printf("\t\t\t\t\t|**********************************************************************|\n");
	char q[4][5] = { "昵称","境界","经验","道年"};
	printf("\t\t\t\t\t %-18s%-18s%-16s%-10s\n",q[0],q[1],q[2],q[3]);
	for (int i = 0; i < indx; i++)
	{
		if (player[i].exp != 0)
			printf("\t\t\t\t\t %-18s%-18s%-16d%-10d\n", player[i].playerName, player[i].rank, player[i].exp, player[i].time);
	}
	printf("\t\t\t\t\t|**********************************************************************|\n");
}
void hideCursor(int a)
{   //光标隐藏函数
	CONSOLE_CURSOR_INFO cursor_info = { 1, a };//第二个值0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

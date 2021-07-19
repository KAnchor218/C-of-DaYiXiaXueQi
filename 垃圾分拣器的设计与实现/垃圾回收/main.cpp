#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<fstream>

#define USER_FILE	"用户名单.txt"
#define ADMIN_FILE	"管理员名单.txt"
#define TYPE_FILE	"垃圾分类表.txt"
#define TR_RE_FILE	"积分兑换表.txt"
#define PRIZE_FILE	"奖品兑换表.txt"	//全局定义，方便使用


using namespace std;

class User {
protected:
	int id;					//用于循环判断
	string name;				//用户的账号
	string password;			//用户的密码
	int score;				//用户的积分
public:
	User(int i, string a = "Alice", string b = "password", int c = 0) {
		id = i;
		name = a;
		password = b;
		score = c;
	}					//构造函数
	int get_score();			//获取用户的积分
	string get_name();			//获取用户的姓名
	bool check_pass(string in);		//判断密码是否正确
	int add_score(int add);		//增加用户的积分
	string get_file_save_str();		//将用户的积分转化为字符串类别，并和用户的账号密码拼接成字符串形式
};

class Rule_contain {
public:
	string type;					//这个垃圾的类别，比如可回收垃圾
	vector<string> vec_trash;		//这个垃圾分类包含的垃圾
};

class Trash_Reward {
public:
	string trash_name;			//垃圾的名字
	int score;					//垃圾对应的积分
	Trash_Reward(string a = "Alice",int s = 0)
	{
		trash_name = a;
		score = s;
	}
};

class Prize {
public:
	string name;				//奖品的名称
	int score = 0;				//奖品兑换所需积分
};

class Manager {
private:
	vector<User> vec_users;		//构造动态数组来储存用户的数据
	vector<User> vec_admins;		//构造动态数组来储存管理员的数据
	vector<Rule_contain> vec_rule;		//构造动态数组来储存规则库的数据
	vector<Trash_Reward> vec_trash_reward; //构造动态数组来储存每个垃圾及其积分
	vector<Prize> vec_prize;		//构造动态数组来储存奖品及其兑换所需积分
public:
	Manager(string file_users, string file_admins) {
		load_users_from(file_users);
		load_admins_from(file_admins);
		load_ALLrules_from();
	}	//构造函数
	void load_users_from(string filename); //把文件中的用户数据储存在动态数组中
	void load_admins_from(string filename); //把文件中的管理员数据储存在动态数组中
	void save_users_to(string filename); //把用户的数据保存进文件中

	void register_user();			//用户注册
	void user_login();			//用户登录
	void admin_login();			//管理员登录

	void event_loop();			//主菜单
	void throw_trash(User& user);		//用户投放垃圾
	void buy_prize(User& user);		//奖品兑换系统
	void user_loop(User& user);		//用户菜单
	void edit_rules(User& Admin);		//编辑规则库的菜单

	void print_rules();			//显示规则库的内容

	void save_ALLrules_to();		//把修改之后的规则保存到文件中
	void load_ALLrules_from();		//把规则从文件中读出

	void change_rules();			//编辑规则库
};

int User::get_score() {
	return this->score;
}

string User::get_name() {
	return this->name;
}
bool User::check_pass(string in) {
	if (this->password == in)return true;
	return false;
}

int User::add_score(int add) {
	this->score += add;
	return score;
}

string User::get_file_save_str() {
	return name + "\t" + password + "\t" + std::to_string(score);
}

void Manager::load_users_from(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) { //判断文件夹是否存在，不存在输出打印信息，并推出当前程序
		printf("文件没能打开！");
		cout << filename << endl;
		exit(0);   //退出当前运行程序
	}
	vec_users.clear(); //清空动态数组
	int num = 0;
	fin >> num;
	string name, password; //定义两个字符串变量存放用户的账号与密码
	int score; //定义一个整型变量存放用户积分
	for (int i = 1; i <= num; i++) {  //将用户信息保存在动态数组中
		fin >> name;
		fin >> password;
		fin >> score;
		User temp_u(i, name, password, score); //构造User类的对象
		vec_users.push_back(temp_u); //将数据添加到动态数组中
	}

}

void Manager::load_admins_from(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) { //判断文件夹是否存在，不存在输出打印信息，并推出当前程序
		printf("文件没能打开！");
		cout << filename << endl;
		exit(0);
	}
	vec_admins.clear();   //清空动态数组
	int num; 	//定义一个整型变量，用来存放管理员数量
	fin >> num;
	string name, password;   //定义两个字符串变量存放管理员的账号与密码
	int score; 	//定义一个整型变量存放管理员积分
	for (int i = 1; i <= num; i++) {   //将管理员信息保存在动态数组中
		fin >> name;
		fin >> password;
		fin >> score;
		User temp_u(i, name, password, score); //构造User类的对象
		vec_admins.push_back(temp_u);   //将数据添加到动态数组中
	}
}

void Manager::save_users_to(string filename) {   //将用户信息保存到文件中
	ofstream fout(filename);
	if (!fout.is_open()) { //判断文件夹是否存在，不存在输出打印信息，并推出当前程序
		printf("文件没能打开！");
		cout << filename << endl;
		exit(0);
	}
	int num = vec_users.size();   //定义一个整型变量，并将动态数组的大小赋值给该变量
	fout << num << endl;
	for (int i = 0; i < num; i++) { //将用户的数据储存进文件中
		fout << vec_users[i].get_file_save_str() << "\n";
	}
}

void Manager::register_user() { //用户的注册
	system("cls"); 	//清屏函数
	string name, pass;   //定义两个字符串变量存放用户输入的账号与密码
	cout << "\n用户注册界面\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("请输入用户名：");
	cin >> name;
	cout << "\n请输入密码：";
	cin >> pass;
	User new_u(vec_users.size() + 1, name, pass, 0);   //构造User类的对象
	vec_users.push_back(new_u);   //将注册后用户的数据储存在动态数组中
	cout << "\n恭喜你已经注册成功！\n";
	system("pause");  //冻结屏幕，便于观察程序的执行结果
}

void Manager::user_login() {
	system("cls"); 	//清屏函数
	string name, pass; 	//定义两个字符串变量存放用户输入的账号与密码
	cout << "\n用户登录界面\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("请输入用户名：");
	cin >> name;
	cout << "\n请输入密码：";
	cin >> pass;
	int n = vec_users.size(); 	//定义一个整型变量，并将动态数组的大小赋值给该变量
	bool got_this_user = false;
	bool check_pass = false; 	//定义两个布尔型变量，用于判断
	User* p = nullptr; 	 //定义一个对象空指针
	for (int i = 0; i < n; i++) {	  //判断用户的账号与密码是否正确
		if (vec_users[i].get_name() == name) { //判断用户的账号是否正确
			got_this_user = true;
			if (vec_users[i].check_pass(pass)) { //判断用户的密码是否正确
				check_pass = true;
				p = &(vec_users[i]);  //把当前用户信息的地址传给指针p
			}
			break;
		}
	}
	if (!got_this_user) {  //用于判断用户名是否不存在，并输出提示
		printf("\n用户名不存在！请重试！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
	}
	if (got_this_user && !check_pass) {  //用于判断用户密码是否不正确，并输出提示
		printf("\n您输入的账户或者密码有误！请重试！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
	}
	if (got_this_user && check_pass) {  //用于判断是否登陆不成功，并输出提示
		printf("\n登陆成功！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
		user_loop(*p);  //调用用户菜单
	}
}

void Manager::admin_login() {
	system("cls");	//清屏函数
	string name, pass;   //定义两个字符串变量存放用户输入的账号与密码
	cout << "\n管理员登录界面\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("请输入管理员用户名：");
	cin >> name;
	cout << "\n请输入密码：";
	cin >> pass;

	int n = vec_admins.size();   //定义一个整型变量，并将动态数组的大小赋值给该变量
	bool got_this_user = false;
	bool check_pass = false;   //定义两个布尔型变量，用于判断
	User* p = nullptr;   //定义一个对象空指针
	for (int i = 0; i < n; i++) {  //判断管理员的账号与密码是否正确
		if (vec_admins[i].get_name() == name) {  //判断管理员的账号是否正确
			got_this_user = true;
			if (vec_admins[i].check_pass(pass)) {  //判断管理员的密码是否正确
				check_pass = true;
				p = &(vec_admins[i]); //将当前管理员信息的地址传给指针p
			}
			break;
		}
	}
	if (!got_this_user) {  //判断管理员的账号是否不存在，并输出提示
		printf("\n用户名不存在！请重试！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
	}
	if (got_this_user && !check_pass) {   //判断管理员的账号是否不正确，并输出提示
		printf("\n您输入的账户或者密码有误！请重试！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
	}
	if (got_this_user && check_pass) {    //判断管理员的密码是否不正确，并输出提示
		printf("\n管理员登陆成功！\n\n");
		system("pause");  //冻结屏幕，便于观察程序的执行结果
		edit_rules(*p);  //调用编辑规则库的菜单
	}
}

void Manager::event_loop() {  //主菜单函数
	while (1) {
		system("cls"); //清屏函数
		bool if_exit = false; //定义一个布尔型变量，用于判断
		cout << "\n 用户的注册与登录系统 \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << " 1:新用户注册\n";
		cout << " 2.用户登陆 \n";
		cout << " 3.管理员登陆 \n";
		cout << " 4.退 出 系 统 \n";  //菜单样式
		printf("\n");
		cout << " 请选择：";
		int choose = 0;
		cin >> choose;
		switch (choose) {  //根据用户选择调用相应函数
		case 1:this->register_user(); break; //调用用户注册函数
		case 2:this->user_login(); break; //调用用户登陆函数
		case 3:this->admin_login(); break;  //调用管理员登陆函数
		case 4:if_exit = true; break;
		default: break;
		}
		if (if_exit)break;
	}
	this->save_users_to(USER_FILE);  //将用户的信息保存到文件中
	this->save_ALLrules_to();  //将规则库数据保存到文件中
}

void Manager::throw_trash(User& user) {  //用户投放垃圾
	system("cls");  //清屏函数
	bool if_exit = false;  //定义一个布尔型变量，用于判断
	cout << "\n 扔垃圾系统 \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " 请输入要扔掉的垃圾名称：";
	string name;
	int num;
	cin >> name;
	cout << " 请输入要扔掉的垃圾数量：";
	cin >> num;
	if (num <= 0) {  //用于判断输入数量是否出错
		cout << "数量有误！！！！" << endl;
		system("pause");
		return;
	}
	else {  //用于增加用户积分
		int score = 0;
		bool got = false;
		for (auto r = vec_trash_reward.begin(); r != vec_trash_reward.end(); r++) {
			if ((*r).trash_name == name) {  //判断所扔垃圾是否存在
				got = true;
				score = (*r).score; //将垃圾所对应的积分赋值给score 
				break;
			}
		}
		if (!got) {  //判断所扔垃圾是否不存在，并输出提示
			printf("该垃圾不存在！\n");
		}
		else {
			printf("这个用户的分数增加了%d\n", num * score);
			user.add_score(num * score);  //调用函数，实现用户积分的增加
			printf("这个用户现在的分数%d\n", user.get_score());
		}
		got = false;
		string type;
		for (auto r = vec_rule.begin(); r != vec_rule.end() && !got; r++) {
			for (auto rr = (*r).vec_trash.begin(); rr != (*r).vec_trash.end(); rr++) {
				if ((*rr) == name) {
					type = (*r).type;
					got = true;
					break;
				}
			}
		}
		if (got) {
			cout << "垃圾" << "\"" << name << "\"" << "的分类是" << type << endl;
		}
		else {
			cout << "这个垃圾没有被分类！" << endl;
		}
	}
	system("pause");
}

void Manager::buy_prize(User& user) {
	system("cls");
	bool if_exit = false;
	cout << "\n 兑换系统 \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " 请输入要兑换的奖品名称：";
	string name;
	int num;
	cin >> name;
	cout << " 请输入要兑换的奖品数量：";
	cin >> num;
	if (num <= 0) {
		cout << "数量有误！！！！" << endl;
		system("pause");
		return;
	}
	else {
		int score = 0;
		bool got = false;
		for (auto r = vec_prize.begin(); r != vec_prize.end(); r++) {
			if ((*r).name == name) {
				got = true;
				score = (*r).score;
				break;
			}
		}
		if (!got) {
			printf("未找到这个奖品！\n");
		}
		else {
			if (num * score > user.get_score()) {
				printf("这个用户的积分不足！积分有：%d,兑换所有奖品需要%d\n", user.get_score(), num * score);
			}
			else {
				printf("兑换需要的分数%d\n", num * score);
				user.add_score(-1 * num * score);
				printf("这个用户现在的分数%d\n", user.get_score());
			}
		}
	}
	system("pause");
}

void Manager::edit_rules(User& Admin) {
	while (1) {
		system("cls");
		bool if_exit = false;
		cout << "\n 规则管理系统 \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << " 1:展示垃圾分类表\n";
		cout << " 2.修改规则\n";
		cout << " 3.返回主界面\n";
		printf("\n");
		cout << " 请选择：";
		int choose = 0;
		cin >> choose;
		switch (choose) {
		case 1:print_rules(); break;
		case 2:change_rules(); break;
		case 3:if_exit = true; break;
		default: printf("非法输入！\n"); break;
		}
		if (if_exit)break;
	}
	this->save_ALLrules_to();
	system("pause");
}

void Manager::user_loop(User& user) {
	while (1) {
		system("cls");
		bool if_exit = false;
		cout << "\n 用户系统 \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << "用户姓名：\t" << user.get_name() << endl;
		cout << "用户积分\t：" << user.get_score() << endl;
		cout << " 1:扔垃圾\n";
		cout << " 2:兑换奖品\n";
		cout << " 3.返回主界面\n";
		printf("\n");
		cout << " 请选择：";
		int choose = 0;
		cin >> choose;
		switch (choose) {
		case 1:throw_trash(user); break;
		case 2:buy_prize(user); break;
		case 3:if_exit = true; break;
		default:; break;
		}
		if (if_exit)break;
	}
	this->save_users_to(USER_FILE);
}

void Manager::save_ALLrules_to() {
	ofstream fout_rule(TYPE_FILE);
	ofstream fout_trash_reward(TR_RE_FILE);
	ofstream fout_prize(PRIZE_FILE);
	fout_rule << vec_rule.size() << endl;
	for (int i = 0; i < vec_rule.size(); i++) {
		Rule_contain* rule = &vec_rule[i];
		fout_rule << rule->type << "\t" << rule->vec_trash.size() << "\n";
		for (int k = 0; k < rule->vec_trash.size(); k++) {
			fout_rule << rule->vec_trash[k] << "\t";
		}
		fout_rule << "\n";
	}

	fout_trash_reward << vec_trash_reward.size();
	for (int i = 0; i < vec_trash_reward.size(); i++) {
		Trash_Reward* r = &vec_trash_reward[i];
		fout_trash_reward << r->trash_name << "\t" << r->score << "\n";
	}

	fout_prize << vec_prize.size();
	for (int i = 0; i < vec_prize.size(); i++) {
		Prize* r = &vec_prize[i];
		fout_prize << r->name << "\t" << r->score << "\n";
	}
}

void Manager::load_ALLrules_from() {
	ifstream fin_rule(TYPE_FILE);
	ifstream fin_trash_reward(TR_RE_FILE);
	ifstream fin_prize(PRIZE_FILE);
	int num = 0;
	fin_rule >> num;
	string name;
	for (int i = 0; i < num; i++) {
		Rule_contain rc;
		fin_rule >> name;
		rc.type = name;
		int kk = 0;
		fin_rule >> kk;
		for (int j = 0; j < kk; j++) {
			fin_rule >> name;
			rc.vec_trash.push_back(name);
		}
		this->vec_rule.push_back(rc);
	}

	fin_trash_reward >> num;
	for (int i = 0; i < num; i++) {
		Trash_Reward tr;
		fin_trash_reward >> tr.trash_name;
		fin_trash_reward >> tr.score;
		this->vec_trash_reward.push_back(tr);
	}
	fin_prize >> num;
	for (int i = 0; i < num; i++) {
		Prize p;
		fin_prize >> p.name;
		fin_prize >> p.score;
		this->vec_prize.push_back(p);
	}

}
void Manager::change_rules() {
	system("cls");
	bool if_exit = false;
	cout << "\n 规则修改系统 \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " 1:删除分类下垃圾\n";
	cout << " 2:修改分类下垃圾\n";
	cout << " 3.添加分类下垃圾\n";
	printf("\n");
	cout << " 请选择：";
	int choose = 0;
	cin >> choose;

	if (choose < 1 || choose>3) {
		printf("非法输入！\n");
		system("pause");
		return;
	}

	cout << " \n请输入分类名称：";
	string type;
	cin >> type;
	bool got_type = false;
	Rule_contain* p_rc = nullptr;
	for (auto r = vec_rule.begin(); r != vec_rule.end(); r++) {
		if ((*r).type == type) {
			p_rc = &(*r);
			got_type = true;
		}
	}
	if (!got_type) {
		printf("未定义的类型！\n");
		system("pause");
		return;
	}

	if (choose == 1) {
		cout << " \n请输入垃圾名称：";
		string name;
		cin >> name;
		bool got_trash = false;
		bool got_reward = false;
		int num1 = 0;
		int num2 = 0;
		auto this_tr = p_rc->vec_trash.begin();
		for (auto r = p_rc->vec_trash.begin(); r != p_rc->vec_trash.end(); r++) {
			if ((*r) == name) {
				got_trash = true;
				this_tr = r;
			}
		}
		for (int i = 0; i < vec_trash_reward.size(); i++)
		{
			if (vec_trash_reward[i].trash_name == name) {
				got_reward = true;
				num1 = i;
				break;
			}
		}
		if (got_trash) {
			p_rc->vec_trash.erase(this_tr);
			cout << " \n已经删除了" << name << endl;
		}
		else {
			cout << " \n未找到" << name << endl;
		}
		if (got_reward) {
			vec_trash_reward.erase(vec_trash_reward.begin()+num1);
		}
		system("pause");
		return;
	}
	else if (choose == 2) {
		cout << " \n请输入垃圾名称：";
		string name;
		cin >> name;
		bool got_trash = false;
		bool got_reward = false;
		int num = 0;
		string New;
		int Score;
		auto this_tr = p_rc->vec_trash.begin();
		for (auto r = p_rc->vec_trash.begin(); r != p_rc->vec_trash.end(); r++) {
			if ((*r) == name) {
				got_trash = true;
				this_tr = r;
			}
		}
		for (int i = 0; i < vec_trash_reward.size(); i++)
		{
			if (vec_trash_reward[i].trash_name == name) {
				got_reward = true;
				num = i;
				break;
			}
		}
		if (got_trash) {
			printf("请输入新名称：");
			string new_type;
			cin >> new_type;
			(*this_tr) = new_type;
			New = new_type;
			printf("请输入新积分：");
			int score1;
			cin >> score1;
			Score = score1;
			vec_trash_reward[num].trash_name = New;
			vec_trash_reward[num].score = Score;
			printf("修改成功！\n");
		}
		else {
			printf("没有这个垃圾！\n");
		}
		system("pause");
		return;
	}
	else {
		printf("请输入添加的垃圾的名称：");
		string new_name;
		cin >> new_name;
		printf("请输入添加的垃圾的积分：");
		int fen;
		cin >> fen;
		p_rc->vec_trash.push_back(new_name);
		Trash_Reward reward(new_name, fen);
		vec_trash_reward.push_back(reward);
		printf("添加成功！\n");
		system("pause");
		return;
	}
	this->save_ALLrules_to();
	system("pause");
	return;
}

void Manager::print_rules() {
	system("cls");
	printf("垃圾分类表:\n");
	for (int i = 0; i < vec_rule.size(); i++) {
		Rule_contain* rule = &vec_rule[i];
		cout << rule->type << "\t" << rule->vec_trash.size() << "\n";
		for (int k = 0; k < rule->vec_trash.size(); k++) {
			cout << rule->vec_trash[k] << "\t";
		}
		cout << "\n";
	}
	printf("\n积分兑换表:\n");

	for (int i = 0; i < vec_trash_reward.size(); i++) {
		Trash_Reward* r = &vec_trash_reward[i];
		cout << r->trash_name << "\t" << r->score << "\n";
	}
	printf("\n奖品兑换表:\n");

	for (int i = 0; i < vec_prize.size(); i++) {
		Prize* r = &(vec_prize[i]);
		cout << r->name << "\t" << r->score << "\n";
	}
	printf("\n");
	system("pause");
}

int main() {
	Manager manager(USER_FILE, ADMIN_FILE);
	manager.event_loop();
	return 0;
}

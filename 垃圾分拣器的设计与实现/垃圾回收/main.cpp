#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<fstream>

#define USER_FILE	"�û�����.txt"
#define ADMIN_FILE	"����Ա����.txt"
#define TYPE_FILE	"���������.txt"
#define TR_RE_FILE	"���ֶһ���.txt"
#define PRIZE_FILE	"��Ʒ�һ���.txt"	//ȫ�ֶ��壬����ʹ��


using namespace std;

class User {
protected:
	int id;					//����ѭ���ж�
	string name;				//�û����˺�
	string password;			//�û�������
	int score;				//�û��Ļ���
public:
	User(int i, string a = "Alice", string b = "password", int c = 0) {
		id = i;
		name = a;
		password = b;
		score = c;
	}					//���캯��
	int get_score();			//��ȡ�û��Ļ���
	string get_name();			//��ȡ�û�������
	bool check_pass(string in);		//�ж������Ƿ���ȷ
	int add_score(int add);		//�����û��Ļ���
	string get_file_save_str();		//���û��Ļ���ת��Ϊ�ַ�����𣬲����û����˺�����ƴ�ӳ��ַ�����ʽ
};

class Rule_contain {
public:
	string type;					//�����������𣬱���ɻ�������
	vector<string> vec_trash;		//��������������������
};

class Trash_Reward {
public:
	string trash_name;			//����������
	int score;					//������Ӧ�Ļ���
	Trash_Reward(string a = "Alice",int s = 0)
	{
		trash_name = a;
		score = s;
	}
};

class Prize {
public:
	string name;				//��Ʒ������
	int score = 0;				//��Ʒ�һ��������
};

class Manager {
private:
	vector<User> vec_users;		//���춯̬�����������û�������
	vector<User> vec_admins;		//���춯̬�������������Ա������
	vector<Rule_contain> vec_rule;		//���춯̬�������������������
	vector<Trash_Reward> vec_trash_reward; //���춯̬����������ÿ�������������
	vector<Prize> vec_prize;		//���춯̬���������潱Ʒ����һ��������
public:
	Manager(string file_users, string file_admins) {
		load_users_from(file_users);
		load_admins_from(file_admins);
		load_ALLrules_from();
	}	//���캯��
	void load_users_from(string filename); //���ļ��е��û����ݴ����ڶ�̬������
	void load_admins_from(string filename); //���ļ��еĹ���Ա���ݴ����ڶ�̬������
	void save_users_to(string filename); //���û������ݱ�����ļ���

	void register_user();			//�û�ע��
	void user_login();			//�û���¼
	void admin_login();			//����Ա��¼

	void event_loop();			//���˵�
	void throw_trash(User& user);		//�û�Ͷ������
	void buy_prize(User& user);		//��Ʒ�һ�ϵͳ
	void user_loop(User& user);		//�û��˵�
	void edit_rules(User& Admin);		//�༭�����Ĳ˵�

	void print_rules();			//��ʾ����������

	void save_ALLrules_to();		//���޸�֮��Ĺ��򱣴浽�ļ���
	void load_ALLrules_from();		//�ѹ�����ļ��ж���

	void change_rules();			//�༭�����
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
	if (!fin.is_open()) { //�ж��ļ����Ƿ���ڣ������������ӡ��Ϣ�����Ƴ���ǰ����
		printf("�ļ�û�ܴ򿪣�");
		cout << filename << endl;
		exit(0);   //�˳���ǰ���г���
	}
	vec_users.clear(); //��ն�̬����
	int num = 0;
	fin >> num;
	string name, password; //���������ַ�����������û����˺�������
	int score; //����һ�����ͱ�������û�����
	for (int i = 1; i <= num; i++) {  //���û���Ϣ�����ڶ�̬������
		fin >> name;
		fin >> password;
		fin >> score;
		User temp_u(i, name, password, score); //����User��Ķ���
		vec_users.push_back(temp_u); //��������ӵ���̬������
	}

}

void Manager::load_admins_from(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) { //�ж��ļ����Ƿ���ڣ������������ӡ��Ϣ�����Ƴ���ǰ����
		printf("�ļ�û�ܴ򿪣�");
		cout << filename << endl;
		exit(0);
	}
	vec_admins.clear();   //��ն�̬����
	int num; 	//����һ�����ͱ�����������Ź���Ա����
	fin >> num;
	string name, password;   //���������ַ���������Ź���Ա���˺�������
	int score; 	//����һ�����ͱ�����Ź���Ա����
	for (int i = 1; i <= num; i++) {   //������Ա��Ϣ�����ڶ�̬������
		fin >> name;
		fin >> password;
		fin >> score;
		User temp_u(i, name, password, score); //����User��Ķ���
		vec_admins.push_back(temp_u);   //��������ӵ���̬������
	}
}

void Manager::save_users_to(string filename) {   //���û���Ϣ���浽�ļ���
	ofstream fout(filename);
	if (!fout.is_open()) { //�ж��ļ����Ƿ���ڣ������������ӡ��Ϣ�����Ƴ���ǰ����
		printf("�ļ�û�ܴ򿪣�");
		cout << filename << endl;
		exit(0);
	}
	int num = vec_users.size();   //����һ�����ͱ�����������̬����Ĵ�С��ֵ���ñ���
	fout << num << endl;
	for (int i = 0; i < num; i++) { //���û������ݴ�����ļ���
		fout << vec_users[i].get_file_save_str() << "\n";
	}
}

void Manager::register_user() { //�û���ע��
	system("cls"); 	//��������
	string name, pass;   //���������ַ�����������û�������˺�������
	cout << "\n�û�ע�����\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("�������û�����");
	cin >> name;
	cout << "\n���������룺";
	cin >> pass;
	User new_u(vec_users.size() + 1, name, pass, 0);   //����User��Ķ���
	vec_users.push_back(new_u);   //��ע����û������ݴ����ڶ�̬������
	cout << "\n��ϲ���Ѿ�ע��ɹ���\n";
	system("pause");  //������Ļ�����ڹ۲�����ִ�н��
}

void Manager::user_login() {
	system("cls"); 	//��������
	string name, pass; 	//���������ַ�����������û�������˺�������
	cout << "\n�û���¼����\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("�������û�����");
	cin >> name;
	cout << "\n���������룺";
	cin >> pass;
	int n = vec_users.size(); 	//����һ�����ͱ�����������̬����Ĵ�С��ֵ���ñ���
	bool got_this_user = false;
	bool check_pass = false; 	//�������������ͱ����������ж�
	User* p = nullptr; 	 //����һ�������ָ��
	for (int i = 0; i < n; i++) {	  //�ж��û����˺��������Ƿ���ȷ
		if (vec_users[i].get_name() == name) { //�ж��û����˺��Ƿ���ȷ
			got_this_user = true;
			if (vec_users[i].check_pass(pass)) { //�ж��û��������Ƿ���ȷ
				check_pass = true;
				p = &(vec_users[i]);  //�ѵ�ǰ�û���Ϣ�ĵ�ַ����ָ��p
			}
			break;
		}
	}
	if (!got_this_user) {  //�����ж��û����Ƿ񲻴��ڣ��������ʾ
		printf("\n�û��������ڣ������ԣ�\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
	}
	if (got_this_user && !check_pass) {  //�����ж��û������Ƿ���ȷ���������ʾ
		printf("\n��������˻������������������ԣ�\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
	}
	if (got_this_user && check_pass) {  //�����ж��Ƿ��½���ɹ����������ʾ
		printf("\n��½�ɹ���\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
		user_loop(*p);  //�����û��˵�
	}
}

void Manager::admin_login() {
	system("cls");	//��������
	string name, pass;   //���������ַ�����������û�������˺�������
	cout << "\n����Ա��¼����\n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	printf("���������Ա�û�����");
	cin >> name;
	cout << "\n���������룺";
	cin >> pass;

	int n = vec_admins.size();   //����һ�����ͱ�����������̬����Ĵ�С��ֵ���ñ���
	bool got_this_user = false;
	bool check_pass = false;   //�������������ͱ����������ж�
	User* p = nullptr;   //����һ�������ָ��
	for (int i = 0; i < n; i++) {  //�жϹ���Ա���˺��������Ƿ���ȷ
		if (vec_admins[i].get_name() == name) {  //�жϹ���Ա���˺��Ƿ���ȷ
			got_this_user = true;
			if (vec_admins[i].check_pass(pass)) {  //�жϹ���Ա�������Ƿ���ȷ
				check_pass = true;
				p = &(vec_admins[i]); //����ǰ����Ա��Ϣ�ĵ�ַ����ָ��p
			}
			break;
		}
	}
	if (!got_this_user) {  //�жϹ���Ա���˺��Ƿ񲻴��ڣ��������ʾ
		printf("\n�û��������ڣ������ԣ�\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
	}
	if (got_this_user && !check_pass) {   //�жϹ���Ա���˺��Ƿ���ȷ���������ʾ
		printf("\n��������˻������������������ԣ�\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
	}
	if (got_this_user && check_pass) {    //�жϹ���Ա�������Ƿ���ȷ���������ʾ
		printf("\n����Ա��½�ɹ���\n\n");
		system("pause");  //������Ļ�����ڹ۲�����ִ�н��
		edit_rules(*p);  //���ñ༭�����Ĳ˵�
	}
}

void Manager::event_loop() {  //���˵�����
	while (1) {
		system("cls"); //��������
		bool if_exit = false; //����һ�������ͱ����������ж�
		cout << "\n �û���ע�����¼ϵͳ \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << " 1:���û�ע��\n";
		cout << " 2.�û���½ \n";
		cout << " 3.����Ա��½ \n";
		cout << " 4.�� �� ϵ ͳ \n";  //�˵���ʽ
		printf("\n");
		cout << " ��ѡ��";
		int choose = 0;
		cin >> choose;
		switch (choose) {  //�����û�ѡ�������Ӧ����
		case 1:this->register_user(); break; //�����û�ע�ắ��
		case 2:this->user_login(); break; //�����û���½����
		case 3:this->admin_login(); break;  //���ù���Ա��½����
		case 4:if_exit = true; break;
		default: break;
		}
		if (if_exit)break;
	}
	this->save_users_to(USER_FILE);  //���û�����Ϣ���浽�ļ���
	this->save_ALLrules_to();  //����������ݱ��浽�ļ���
}

void Manager::throw_trash(User& user) {  //�û�Ͷ������
	system("cls");  //��������
	bool if_exit = false;  //����һ�������ͱ����������ж�
	cout << "\n ������ϵͳ \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " ������Ҫ�ӵ����������ƣ�";
	string name;
	int num;
	cin >> name;
	cout << " ������Ҫ�ӵ�������������";
	cin >> num;
	if (num <= 0) {  //�����ж����������Ƿ����
		cout << "�������󣡣�����" << endl;
		system("pause");
		return;
	}
	else {  //���������û�����
		int score = 0;
		bool got = false;
		for (auto r = vec_trash_reward.begin(); r != vec_trash_reward.end(); r++) {
			if ((*r).trash_name == name) {  //�ж����������Ƿ����
				got = true;
				score = (*r).score; //����������Ӧ�Ļ��ָ�ֵ��score 
				break;
			}
		}
		if (!got) {  //�ж����������Ƿ񲻴��ڣ��������ʾ
			printf("�����������ڣ�\n");
		}
		else {
			printf("����û��ķ���������%d\n", num * score);
			user.add_score(num * score);  //���ú�����ʵ���û����ֵ�����
			printf("����û����ڵķ���%d\n", user.get_score());
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
			cout << "����" << "\"" << name << "\"" << "�ķ�����" << type << endl;
		}
		else {
			cout << "�������û�б����࣡" << endl;
		}
	}
	system("pause");
}

void Manager::buy_prize(User& user) {
	system("cls");
	bool if_exit = false;
	cout << "\n �һ�ϵͳ \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " ������Ҫ�һ��Ľ�Ʒ���ƣ�";
	string name;
	int num;
	cin >> name;
	cout << " ������Ҫ�һ��Ľ�Ʒ������";
	cin >> num;
	if (num <= 0) {
		cout << "�������󣡣�����" << endl;
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
			printf("δ�ҵ������Ʒ��\n");
		}
		else {
			if (num * score > user.get_score()) {
				printf("����û��Ļ��ֲ��㣡�����У�%d,�һ����н�Ʒ��Ҫ%d\n", user.get_score(), num * score);
			}
			else {
				printf("�һ���Ҫ�ķ���%d\n", num * score);
				user.add_score(-1 * num * score);
				printf("����û����ڵķ���%d\n", user.get_score());
			}
		}
	}
	system("pause");
}

void Manager::edit_rules(User& Admin) {
	while (1) {
		system("cls");
		bool if_exit = false;
		cout << "\n �������ϵͳ \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << " 1:չʾ���������\n";
		cout << " 2.�޸Ĺ���\n";
		cout << " 3.����������\n";
		printf("\n");
		cout << " ��ѡ��";
		int choose = 0;
		cin >> choose;
		switch (choose) {
		case 1:print_rules(); break;
		case 2:change_rules(); break;
		case 3:if_exit = true; break;
		default: printf("�Ƿ����룡\n"); break;
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
		cout << "\n �û�ϵͳ \n";
		for (int i = 0; i < 30; i++)printf("_");
		printf("\n\n");
		cout << "�û�������\t" << user.get_name() << endl;
		cout << "�û�����\t��" << user.get_score() << endl;
		cout << " 1:������\n";
		cout << " 2:�һ���Ʒ\n";
		cout << " 3.����������\n";
		printf("\n");
		cout << " ��ѡ��";
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
	cout << "\n �����޸�ϵͳ \n";
	for (int i = 0; i < 30; i++)printf("_");
	printf("\n\n");
	cout << " 1:ɾ������������\n";
	cout << " 2:�޸ķ���������\n";
	cout << " 3.��ӷ���������\n";
	printf("\n");
	cout << " ��ѡ��";
	int choose = 0;
	cin >> choose;

	if (choose < 1 || choose>3) {
		printf("�Ƿ����룡\n");
		system("pause");
		return;
	}

	cout << " \n������������ƣ�";
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
		printf("δ��������ͣ�\n");
		system("pause");
		return;
	}

	if (choose == 1) {
		cout << " \n�������������ƣ�";
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
			cout << " \n�Ѿ�ɾ����" << name << endl;
		}
		else {
			cout << " \nδ�ҵ�" << name << endl;
		}
		if (got_reward) {
			vec_trash_reward.erase(vec_trash_reward.begin()+num1);
		}
		system("pause");
		return;
	}
	else if (choose == 2) {
		cout << " \n�������������ƣ�";
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
			printf("�����������ƣ�");
			string new_type;
			cin >> new_type;
			(*this_tr) = new_type;
			New = new_type;
			printf("�������»��֣�");
			int score1;
			cin >> score1;
			Score = score1;
			vec_trash_reward[num].trash_name = New;
			vec_trash_reward[num].score = Score;
			printf("�޸ĳɹ���\n");
		}
		else {
			printf("û�����������\n");
		}
		system("pause");
		return;
	}
	else {
		printf("��������ӵ����������ƣ�");
		string new_name;
		cin >> new_name;
		printf("��������ӵ������Ļ��֣�");
		int fen;
		cin >> fen;
		p_rc->vec_trash.push_back(new_name);
		Trash_Reward reward(new_name, fen);
		vec_trash_reward.push_back(reward);
		printf("��ӳɹ���\n");
		system("pause");
		return;
	}
	this->save_ALLrules_to();
	system("pause");
	return;
}

void Manager::print_rules() {
	system("cls");
	printf("���������:\n");
	for (int i = 0; i < vec_rule.size(); i++) {
		Rule_contain* rule = &vec_rule[i];
		cout << rule->type << "\t" << rule->vec_trash.size() << "\n";
		for (int k = 0; k < rule->vec_trash.size(); k++) {
			cout << rule->vec_trash[k] << "\t";
		}
		cout << "\n";
	}
	printf("\n���ֶһ���:\n");

	for (int i = 0; i < vec_trash_reward.size(); i++) {
		Trash_Reward* r = &vec_trash_reward[i];
		cout << r->trash_name << "\t" << r->score << "\n";
	}
	printf("\n��Ʒ�һ���:\n");

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

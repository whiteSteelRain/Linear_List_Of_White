#include <iostream>
using namespace std;

struct term {
	float coef;    //ϵ��
	int expn;    //ָ��
	term* next;
	term* prior;
};

class Polynomial {
private:
	term* front;

public:
	Polynomial();
	//void Copy(Polynomial& E);
	void Input();//����
	~Polynomial();
	void Print();
	void Add(Polynomial& A);
	void Minus(Polynomial& B);
	void Multiply(Polynomial& C);
	void dx();
	float Get(int x);
	void Sort();//���մ�������
	void Assign(Polynomial &P);//��ֵ
};

Polynomial::Polynomial() {
	front = new term;
	front->next = NULL;
	front->prior = NULL;

}

void Polynomial::Assign(Polynomial& P) {
	//������ֵ
	P.Sort();
	//��һ��������������нڵ�
	term* p = front->next;
	term* t;
	while (p)
	{
		t = p;
		p = p->next;
		delete t;
	}
	//�ڶ���������P�Ľڵ�
	p = front;
	term* q = P.front->next;
	while (q)
	{
		term* s = new term;
		s->coef = q->coef;
		s->expn = q->expn;
		s->prior = p;
		p->next = s;
		

		p = s;


		q = q->next;
	}
	p->next = NULL;




}

void Polynomial::Input() {
	int n;
	term* r = front;
	//n�����������
	cout << "��������Ҫ���������";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "���ǵ�" << (i + 1) << "��" << endl;
		cout << "���������ϵ��:";
		term* p = new term;
		cin >> p->coef;
		cout << endl;
		cout << "���������ָ��:";
		cin >> p->expn;

		p->prior = r;
		r->next = p;
		r = p;


	}
	r->next = NULL;
	
}

void Polynomial::Print() {
	term* p = front->next;
	int counter = 1;
	while (p)
	{
	
		if (counter != 1 && p->coef > 0) cout << "+";
		if (p->coef < 0 && p->coef != -1) cout << p->coef << "x^";
		if (p->coef == -1) cout << "-x^";
		if (p->coef == 1)cout << "x^";
		

		
		if (p->coef > 0 && p->coef != 1) cout << p->coef<<"x^";
			
		if(p->expn)
			cout << p->expn;
		else {
			if(p->coef<0)
			cout << p->coef;
			
			if (counter != 1 && p->coef > 0) 
				cout << "+"<<p->coef;
			
		}

			counter++;
		

		//cout << "���ǵ�" << counter++ << "��Ϊ" << p->coef << "x^" << p->expn << endl;
		p = p->next;
	}

}

void Polynomial::Sort() {
	
	Polynomial A;
	term* p = front;
	term* q = p;
	term* temp = q;
	int Minexpn = 0;
	while (q->next)
	{
		p = q->next;
		
		Minexpn = 10001;



	while (p)
	{
		if (p->expn < Minexpn)
		{
			Minexpn = p->expn;
			temp = p;
		}
		p = p->next;

	}
	if (temp->next)
	{
	temp->prior->next = temp->next;
	temp->next->prior = temp->prior;
	}
	else {
		temp->prior->next = NULL;
	}

	
	temp->next = q->next;
	temp->prior = q;
	q->next = temp;

    if (temp->next)
		temp->next->prior = temp;


	q = q->next;

	}
	p = front;
	q = p;
	while (p)
	{
		if (p->coef == 0)
		{
			q = p;
			p->prior->next = p->next;
			if(p->next)
			p->next->prior = p->prior;
		}
		p = p->next;
	}





}

void Polynomial::Add(Polynomial& A) {
	A.Sort();
	term* p = front->next;//ȡpΪ���ӵ�������
	term* q = A.front->next;
	term* t = q;
	while (p)
	{
		if(q && p->expn > q->expn)
		{
			while (  q && p->expn > q->expn)
			{

				q = q->next;
			t->next = p->prior->next;
			p->prior->next = t;
			t->prior = p->prior;
			t->next->prior = t;
				
			
			t = q;

			}
			
		}


		if (q && p->expn == q->expn)
		{
			p->coef += q->coef;
			





			q = q->next;
			t = q;
		}
		if (! p->next)
		{
			if (q && p->expn < q->expn)
			{
				q = q->next;
				t->prior->next = t->next;
				if (t->next) t->next->prior = t->prior;

				t->next = p->next;
				p->next = t;
				t->prior = p;

				//if (t->next) t->next->prior = t;


				t = q;
				//p = p->next;
			}
		}


		p = p->next;
	}
	A.front->next = NULL;//��һ��������Ҫ����bug���˰�Сʱ���ģ�����Ϊ���A�Ľڵ�������֮��
	//��A������ʱ��A��ͷ����next��Ұָ�룬�����޷��������Ӷ�������
	//������ ����ʽ.exe ��ִ�жϵ�ָ��(__debugbreak()�������Ƶ���)����bug
}

void Polynomial::Minus(Polynomial& B) {
	B.Sort();
	term* p = B.front->next;
	while (p)
	{
		p->coef *= (-1);
		p = p->next;
	}
	Add(B);

}

void Polynomial::Multiply(Polynomial& C) {
	C.Sort();

	term* p = front->next;


	Polynomial T;
	T.Assign(C);
	Polynomial Answer;
	Answer.Assign(C);



	term* q =C.front->next;
	term* t = q;

	while (p)
	{
		while (q)
		{
			q->coef *= p->coef;
			q->expn += p->expn;
			q = q->next;
		}//ÿ��������Ӧ�����
		
		Answer.Add(C);
		
		Answer.Sort();

		C.Assign(T);

		Answer.Sort();
		p = p->next;
		q = C.front->next;
	}
	Answer.Minus(T);
	Assign(Answer);
}

void Polynomial::dx() {
	term* p = front->next;
	term* t = p;
	while (p)
	{
		if (p->expn == 0)
		{

			p->prior->next = p->next;
			if (p->next) p->next->prior = p->prior;
			t = p;
			delete t;
		}
		else {
			
			p->coef *= p->expn;
			p->expn--;
		}
		p = p->next;
	}
	Sort();
}

float Polynomial::Get(int x)
{
	float value = 0;
	int power = 1;
	term* p = front->next;
	while (p)
	{
		for (int i = 0; i < p->expn; i++)
		{
			power *= x;
		}
		value += (p->coef * power);
		p = p->next;
		power = 1;
	}

	return value;


}

Polynomial::~Polynomial() {

	term* p = front;
	while (p)
	{
		front = p;
		p = p->next;
		delete front;

	}

}
int main() {
	Polynomial john;
	john.Input();
	john.Sort();
	cout << endl;
	//Polynomial wick;
	//wick.Input();

	
	
	john.Print();
	cout << endl;
	cout << john.Get(3);
	return 0;
}
#ifndef SUDOKU_DANCINGLINKS_H
#define SUDOKU_DANCINGLINKS_H

#include <iostream>
#include <array>
#include <random>
#include<cstring>
#include<algorithm>

using namespace std;
constexpr auto mx = 400000; //��ʵ������ô��ֻҪ����729*324����;

class DLX {
private:
	int n, m, cnt;//����ĳ������������
	int l[mx], r[mx], u[mx], d[mx], row[mx], col[mx];//ÿ��������ң����£��У�����Ϣ
	int h[mx];//ÿ�е�ͷ���
	int s[mx];//ÿ�еĽ����
	int ansk[mx];//ansk[] װ�𰸣�ѡ���ļ��У�
	void init(int _n, int _m) {
		n = _n, m = _m;
		int i;
		for (i = 0; i <= m; i++) {
			r[i] = i + 1; l[i] = i - 1; u[i] = d[i] = i;
		}
		r[m] = 0;//m�ұ���0
		l[0] = m;//0�����m
		memset(h, -1, sizeof(h));
		memset(s, 0, sizeof(s));
		cnt = m + 1;//��ʼʱ��m����㣨0���͸���ͷ��㣩
	}//��ʼ��������ÿ�е�ͷ

	void remove(int c) {
		r[l[c]] = r[c], l[r[c]] = l[c];
		for (int i = d[c]; i != c; i = d[i]) {
			for (int j = r[i]; j != i; j = r[j]) {
				u[d[j]] = u[j];
				d[u[j]] = d[j];
				s[col[j]]--;
			}
		}
	}//ɾ��c�к�c�����е����

	void resume(int c) {
		for (int i = u[c]; i != c; i = u[i]) {
			for (int j = l[i]; j != i; j = l[j]) {
				u[d[j]] = j;
				d[u[j]] = j;
				s[col[j]]++;
			}
		}
		r[l[c]] = c;
		l[r[c]] = c;
	} //�ָ�c�к�c�����е����

public:
	DLX() {
		init(729, 324);
	}

	void link(int R, int C) {
		s[C]++;
		row[cnt] = R;
		col[cnt] = C;
		u[cnt] = C;
		d[cnt] = d[C];
		u[d[C]] = cnt;
		d[C] = cnt;
		if (h[R] < 0) h[R] = r[cnt] = l[cnt] = cnt;//����û�б�ĵ�,�ѵ�һ������ĵ���Ϊ���е���ͷ���
		else {
			r[cnt] = h[R];
			l[cnt] = l[h[R]];
			r[l[h[R]]] = cnt;
			l[h[R]] = cnt;
		}
		cnt++;
	}//��r��c�в����

	bool dance(int deep, array<array <int, 9>, 9> &sudoku) {
		if (r[0] == 0) {
			int x, y, v;
			for (int i = 0; i < deep; i++) {
				x = (ansk[i] - 1) / 9 / 9;
				y = (ansk[i] - 1) / 9 % 9;
				v = (ansk[i]) % 9;//������Ϣת���ɶ�Ӧ�ĵ��ֵ
				if (v == 0)v = 9;//��ֹ9�ı���%9==0
				sudoku[x][y] = v;
			}
			return true;//ֻҪ��һ���
		}
		int c = r[0];
		for (int i = r[0]; i != 0; i = r[i])if (s[i] < s[c])c = i;//�ҵ������ٵ���
		remove(c);
		for (int i = d[c]; i != c; i = d[i]) {
			ansk[deep] = row[i];
			for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
			if (dance(deep + 1, sudoku)) return true;//ֻҪ��һ���
			for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
		}
		resume(c);
		return false;
	}
};
#endif SUDOKU_DANCINGLINKS_H
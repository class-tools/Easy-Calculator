/*
Easy-Calculator Main File 1.0.1
This source code file is under MIT License.
Copyright (c) 2022 Class Tools Develop Team
Contributors: tigerchen-coder
*/
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<stack>
#include<map>
using namespace std;
const int maxn = 100005;
// Big Number Template
struct bign{
    int d[maxn], len;
    bool changed;
	void clean() { while(len > 1 && !d[len-1]) len--; }
 
    bign() 			{ memset(d, 0, sizeof(d)); len = 1; changed = 0;}
    bign(int num) 	{ *this = num; } 
	bign(char* num) { *this = num; }
	bign(string num){ *this = num; }
	bign operator = (const string num){
		//cout<<"emm..."<<endl;
		memset(d,0,sizeof(d)); len = num.size(); changed = 1;
		for(int i = 0; i < len; i++) d[i] = num[len-i-1] - '0';
		clean();
		return *this;
	}
    bign operator = (const char* num){
        memset(d, 0, sizeof(d)); len = strlen(num); changed = 1;
        for(int i = 0; i < len; i++) d[i] = num[len-1-i] - '0';
        clean();
		return *this;
    }
    bign operator = (int num){
        char s[20]; sprintf(s, "%d", num); changed = 1;
        *this = s;
		return *this;
    }
 
    bign operator + (const bign& b){
        bign c = *this; int i;
        for (i = 0; i < b.len; i++){
        	c.d[i] += b.d[i];
        	if (c.d[i] > 9) c.d[i]%=10, c.d[i+1]++;
		}
		while (c.d[i] > 9) c.d[i++]%=10, c.d[i]++;
		c.len = max(len, b.len);
		if (c.d[i] && c.len <= i) c.len = i+1;
        return c;
    }
    bign operator - (const bign& b){
        bign c = *this; int i;
        for (i = 0; i < b.len; i++){
        	c.d[i] -= b.d[i];
        	if (c.d[i] < 0) c.d[i]+=10, c.d[i+1]--;
		}
		while (c.d[i] < 0) c.d[i++]+=10, c.d[i]--;
		c.clean();
		return c;
    }
    bign operator * (const bign& b)const{
        int i, j; bign c; c.len = len + b.len; 
        for(j = 0; j < b.len; j++) for(i = 0; i < len; i++) 
			c.d[i+j] += d[i] * b.d[j];
        for(i = 0; i < c.len-1; i++)
            c.d[i+1] += c.d[i]/10, c.d[i] %= 10;
        c.clean();
		return c;
    }
    bign operator / (const bign& b){
    	int i, j;
		bign c = *this, a = 0;
    	for (i = len - 1; i >= 0; i--)
    	{
    		a = a*10 + d[i];
    		for (j = 0; j < 10; j++) if (a < b*(j+1)) break;
    		c.d[i] = j;
    		a = a - b*j;
    	}
    	c.clean();
    	return c;
    }
    bign operator % (const bign& b){
    	int i, j;
		bign a = 0;
    	for (i = len - 1; i >= 0; i--)
    	{
    		a = a*10 + d[i];
    		for (j = 0; j < 10; j++) if (a < b*(j+1)) break;
    		a = a - b*j;
    	}
    	return a;
    }
	bign operator += (const bign& b){
        *this = *this + b;
        return *this;
    }
 
    bool operator <(const bign& b) const{
        if(len != b.len) return len < b.len;
        for(int i = len-1; i >= 0; i--)
            if(d[i] != b.d[i]) return d[i] < b.d[i];
        return false;
    }
    bool operator >(const bign& b) const{return b < *this;}
    bool operator<=(const bign& b) const{return !(b < *this);}
    bool operator>=(const bign& b) const{return !(*this < b);}
    bool operator!=(const bign& b) const{return b < *this || *this < b;}
    bool operator==(const bign& b) const{return !(b < *this) && !(b > *this);}
 
    string str() const{
        char s[maxn]={};
        for(int i = 0; i < len; i++) s[len-1-i] = d[i]+'0';
        return s;
    }
}jia,jian,cheng,chu,zkh,ERR;istream& operator >> (istream& in, bign& x){
    string s;
    in >> s;
    x = s.c_str();
    return in;
}ostream& operator << (ostream& out, const bign& x){
    out << x.str();
    return out;
}
stack<bign> st;
map<string,bign> mp;
bign zuo(string s){
	//cout<<"1"<<endl;
	while(!st.empty()) st.pop();
	string t="";
	char c;
	int l=s.size();
	bign now=0,n2;
	bool get=0;
	st.push(zkh);
	s+=')';
	for(int i=0;i<=l;i++){
		c=s[i];
		if((c<'A'||c>'Z')&&(c<'a'||c>'z')){
			if(mp[t].changed==0){
				cout<<"ERROR:Variable not exist!"<<endl;
				return ERR;
			}
			now=mp[t];
		}
		if(c=='+'||c=='-'||c=='*'||c=='/'||c==')'){
			if(st.top()==cheng){
				st.pop();
				now=now*st.top();
				st.pop();
			}
			if(st.top()==chu){
				st.pop();
				if(st.top()==bign(0)){
					cout<<"ERROR:Divided by zero!"<<endl;
					return ERR;
				}
				now=now/st.top();
				st.pop();
			}
			//cout<<"QA";
			if(get) st.push(now);
			//cout<<"Q"<<endl;
			now=0;
			get=0;
		}
		if(c=='+') st.push(jia);
		else if(c=='-') st.push(jian);
		else if(c=='*') st.push(cheng);
		else if(c=='/') st.push(chu);
		else if(c=='(') st.push(zkh);
		else if(c==')'){
			n2=0;
			while(st.top()!=zkh){
				n2=st.top();
				st.pop();
				if(st.top()==jian) now=now-n2;
				else now=now+n2;
				if(st.top()!=zkh) st.pop();
			}
			st.pop();
			if(!st.empty()&&(st.top()==cheng)){
				st.pop();
				now=now*st.top();
				st.pop();
			}
			if(!st.empty()&&(st.top()==chu)){
				st.pop();
				if(st.top()==bign(0)){
					cout<<"ERROR:Divided by zero!"<<endl;
					return ERR;
				}
				now=now/st.top();
				st.pop();
			}
			st.push(now);
			now=0;
			continue;
		}
		//cout<<i<<"ok"<<endl;
		else if(c>='0'&&c<='9') now=now*10+(c-'0'),get=1;
		else if(c>='A'&&c<='Z'||c>='a'&&c<='z') t+=c;
		else{
			cout<<"ERROR:Redunant symbol!"<<endl;
			return ERR;
		}
	}
	return mp["_"]=st.top();
}
int main(){
	jia.len=-1;jian.len=-2;cheng.len=-3;chu.len=-4;zkh.len=-5;
	ERR.len=-123;
	//zuo("0");
	//ios::sync_with_stdio(0);
	int op;string x,y;bign res;
	//cout<<"???"<<endl;
	//cout<<zuo("0")<<endl;
	cout<<"Easy calculater VER 1.0.0"<<endl;
    cout<<"Input \"1 X Y\" assign Y to X (X is a string, Y is an expression or a number)"<<endl;
    cout<<"Input \"2 X\" evaluates the value of expression X"<<endl;
    cout<<"Input \"3\" to quit"<<endl;
    cout<<"\"_\" means last result,press ENTER to confirm"<<endl;
    cout<<"Do not input anything that does not conform to the format"<<endl;
	while(1){//maybe bug(format error)
		cout<<">>>";
		cin>>op;
		if(op==1){
			cin>>x>>y;
			res=zuo(y);
			if(res!=ERR){
				mp[x]=res;
				cout<<"Now "<<x<<" is "<<mp[x]<<endl;
			}
			else cout<<"Assign failed"<<endl;
		}else if(op==2){
			cin>>x;
			//cout<<"started!"<<endl;
			res=zuo(x);
			if(res!=ERR) cout<<res<<endl;
		}else break;
	}
	return 0;
}

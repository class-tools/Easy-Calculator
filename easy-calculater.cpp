/*
Web-Class-Helper Main File 1.0.0
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
// Big Number Template==============================================================================
struct bign{
    int d[maxn], len;
    bool changed, fh;
	void clean() { while(len > 1 && !d[len-1]) len--; }
 
    bign() 			{ memset(d, 0, sizeof(d)); len = 1; changed = 0;}
    bign(int num) 	{ *this = num; } 
	bign(char* num) { *this = num; }
	bign(string num){ *this = num; }
	bign operator = (const string num){
		int t=0;
		if(num[0] == '-') fh = 1,t = 1;
		memset(d, 0, sizeof(d)); len = num.size(); changed = 1;
		for(int i = 0; i < len; i++) d[i] = num[t+len-i-1] - '0';
		clean();
		return *this;
	}
    bign operator = (const char* num){
		int t=0;
		if(num[0] == '-') fh = 1,t = 1;
        memset(d, 0, sizeof(d)); len = strlen(num); changed = 1;
        for(int i = 0; i < len; i++) d[i] = num[t+len-1-i] - '0';
        clean();
		return *this;
    }
    bign operator = (int num){
        char s[20]; sprintf(s, "%d", num); changed = 1;
        *this = s;
		return *this;
    }
    bool operator <(const bign& b) const{
    	if(fh&&!b.fh) return true;
    	if(!fh&&b.fh) return false;
    	bign t,a=*this,c=b;
    	if(fh&&b.fh) t=a,a=c,c=t;
        if(len != c.len) return len < c.len;
        for(int i = len-1; i >= 0; i--)
            if(d[i] != c.d[i]) return d[i] < c.d[i];
        return false;
    }
    bool operator >(const bign& b) const{return b < *this;}
    bool operator<=(const bign& b) const{return !(b < *this);}
    bool operator>=(const bign& b) const{return !(*this < b);}
    bool operator!=(const bign& b) const{return b < *this || *this < b;}
    bool operator==(const bign& b) const{return !(b < *this) && !(b > *this);}
    bign operator - (const bign& b)const;
    bign operator + (const bign& b){
        bign c = *this,dd=b; int i;
        if(!c.fh&&b.fh){
        	dd.fh=0;
        	return c-dd;
		}
		if(c.fh&&!b.fh){
			c.fh=0;
			return dd-c;
		}
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
        bign c = *this,dd=b,t; int i;
        if(b.fh){
        	dd.fh=0;
        	return c+dd;
		}
		if(c<b) dd.fh=1,t=c,c=dd,dd=t;
        for (i = 0; i < dd.len; i++){
        	c.d[i] -= dd.d[i];
        	if (c.d[i] < 0) c.d[i]+=10, c.d[i+1]--;
		}
		while (c.d[i] < 0) c.d[i++]+=10, c.d[i]--;
		c.clean();
		return c;
    }
    bign operator * (const bign& b)const{
        int i, j; bign c; c.len = len + b.len; c.fh=fh^b.fh;
        for(j = 0; j < b.len; j++) for(i = 0; i < len; i++) 
			c.d[i+j] += d[i] * b.d[j];
        for(i = 0; i < c.len-1; i++)
            c.d[i+1] += c.d[i]/10, c.d[i] %= 10;
        c.clean();
		return c;
    }
    bign operator / (const bign& b){
    	int i, j;
		bign c = *this, a = 0; c.fh=fh^b.fh;
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
		bign a = 0,c=b;
		c.fh=0;
    	for (i = len - 1; i >= 0; i--)
    	{
    		a = a*10 + d[i];
    		for (j = 0; j < 10; j++) if (a < c*(j+1)) break;
    		a = a - c*j;
    	}
    	return a;
    }
    string str() const{
        char s[maxn]={};
        int t=0;
        if(fh) s[0]='-',t++;
        for(int i = 0; i < len; i++) s[len+t-1-i] = d[i]+'0';
        return s;
    }
}jia,jian,cheng,chu,zkh,ERR;
istream& operator >> (istream& in, bign& x){
    string s;
    in >> s;
    x = s.c_str();
    return in;
}
ostream& operator << (ostream& out, const bign& x){
    out << x.str();
    return out;
}
// Funtions=========================================================================================
bign _max(bign a,bign b){return a>b?a:b;}
bign _min(bign a,bign b){return a<b?a:b;}
bign _abs(bign a){
	bign x=a;
	x.fh=0;
	return x;
}
bign _pow(bign a,bign b){
	bign ans=bign("1");
	while(b>bign("0")){
		if((b.d[b.len-1])&1) ans=ans*a;
		a=a*a;
		b=b/2;
	}
	return ans;
}
bign _sqrt(bign x){
	bign l="0",r=x+1,mid=(l+r)/2;
	while(mid-l>bign("0")&&r-mid>bign("0")){
		if((mid*mid-x)*(l*l-x)<0) r=mid;
		else l=mid;
		mid=(l+r)/2;
	}
	return mid;
}

// Calculate Funtion================================================================================
stack<bign> st;
map<string,bign> mp;
bign zuo(string s){
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
		if(c=='#'){
			if(t!=""){
				
			}
		}
		if((c<'A'||c>'Z')&&(c<'a'||c>'z')&&c!='_'&&t!=""){
			if(mp[t].changed==0){
				cout<<"ERROR:Variable not exist!"<<endl;
				return ERR;
			}
			st.push(mp[t]);
			t="";
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
			if(get) st.push(now);
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
		else if(c>='0'&&c<='9') now=now*10+(c-'0'),get=1;
		else if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||c=='_') t+=c;
		else{
			cout<<"ERROR:Redunant symbol!"<<endl;
			return ERR;
		}
	}
	return mp["_"]=st.top();
}
// Main Function====================================================================================
int main(){
	jia.len=-1;jian.len=-2;cheng.len=-3;chu.len=-4;zkh.len=-5;
	ERR.len=-123;
	//ios::sync_with_stdio(0);
	int op;string x,y;bign res;
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
			res=zuo(x);
			if(res!=ERR) cout<<res<<endl;
		}else break;
	}
	return 0;
}

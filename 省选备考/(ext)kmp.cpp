void kmp(char s1[], int next1[], char s2[], int next2[]){
    int len1=strlen(s1+1), len2=strlen(s2+1);
    int j=0;
    forto(i,1,len1){
        while (j && s1[i]!=s2[j+1]) j=next2[j];
        if (s1[i]==s2[j+1]) j++;
        next1[i]=j;
    }
}
kmp(s+1, next+1, s, next);

void extkmp(char s1[], int ext1[], char s2[], int ext2[]){
	int len1=strlen(s1+1), len2=strlen(s2+1);
	int k=1, j=0;
	while (s1[j+1]==s2[j+1]&&j<len1) j++;
	ext1[1]=j;
	for (int i=2;i<=len1;i++){
		int len=ext2[i-k+1];
		if (i+len-1<j) ext1[i]=len;
		else {
			len=j-i+1;
			if (len<0) len=0;
			while (s1[i+len]==s2[len+1]&& len<len2) len++;
			ext1[i]=len;
			k=i; j=i+len-1;
		}
	}
}
extkmp(s+1, ext+1, s, ext);

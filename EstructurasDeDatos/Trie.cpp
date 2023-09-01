struct trie{
    int len,id;
    int children[26];
    trie(int _id){
        len=0,id=_id;
        for(int i=0;i<26;i++)children[i]=-1;
    }
};vector<trie>Trie;Trie.push_back(trie());
void inserString(string str,int root){
    int aux=root;
    for(int i=0;i<str.size();i++){
        int index=str[i]-'a';
        if(Trie[aux].children[index]==-1){
            Trie.push_back(trie(Trie.size()));
            Trie[aux].children[index]=Trie.size()-1;
        }
        aux=Trie[aux].children[index];
    }
    Trie[aux].len=str.size();
}
bool existInTrie(string str,int root){
    int aux=root;
    for(int i=0;i<str.size();i++){
        int index=str[i]-'a';
        if(Trie[aux].children[index]==-1) return false;
        aux=Trie[aux].children[index];
    }
    return Trie[aux].len;
}
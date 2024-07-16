const static int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }

struct TrieNode
{
    TrieNode *children[ALPHABETS];
    bool terminal;

    TrieNode() : terminal(false)
    {
        memset(children, 0, sizeof(children));
    }

    void insert(const string::iterator key, const string::iterator end)
    {
        if (key == end)
            terminal = true;
        else
        {
            int next = toNumber(*key);
            if (children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1, end);
        }
    }

    TrieNode *find(const string::iterator key, const string::iterator end)
    {
        if (key == end)
            return this;
        TrieNode *node = NULL;

        if (*key == '.')
        {
            for (char ch = 'a'; ch <= 'z'; ++ch)
            {
                int next = toNumber(ch);
                if (children[next] != NULL)
                {
                    node = children[next]->find(key + 1, end);
                    if ((node != NULL) && (node->terminal))
                        return node;
                }
            }
        }
        else
        {
            int next = toNumber(*key);
            if (children[next] == NULL)
                return NULL;
            node = children[next]->find(key + 1, end);
        }

        return node;
    }
};

class WordDictionary
{
public:
    TrieNode *root;

    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(string word)
    {
        root->insert(word.begin(), word.end());
    }

    bool search(string word)
    {
        TrieNode *node = root->find(word.begin(), word.end());
        return (node != NULL) && (node->terminal);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
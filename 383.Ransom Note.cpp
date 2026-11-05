class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (magazine.size() < ransomNote.size()) { return false; }

        std::array<int, 26> count {};

        for (const char& c : magazine) {
            ++count[c - 'a'];
        }

        for (const char& c : ransomNote) {
            if (--count[c - 'a'] < 0) { return false; }
        }

        return true;
    }
};

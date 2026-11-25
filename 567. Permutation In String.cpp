class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s2.empty()) { return false; }
        if (s1.length() > s2.length()) { return false; }

        const int n = s1.length();

        array<int, 26> countS1{};  // filled in initially
        array<int, 26> countS2{};  // current char count of the window into s2

        for (const char& c : s1) {
            ++countS1[c - 'a'];
        }

        size_t f {0};  // front : will lead the window
        size_t b {0};  // back : will trail the window

        while (f < s2.length()) {
            ++countS2[s2[f] - 'a'];
            ++f;

            if (f - b > n) {
                --countS2[s2[b] - 'a'];
                ++b;
            }

            if (countS1 == countS2) { return true; }
        }

        return false;
    }
};

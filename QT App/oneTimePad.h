 #include <vector>

class oneTimePad
{
public:
    oneTimePad();
    void setKey(const std::vector<bool> &newkey)
    {
        key = newkey;
    }
    std::vector<bool> Encrypt(const std::vector<bool> &seq);
private:
    std::vector<bool> key;
};
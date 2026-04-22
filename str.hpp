#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char* data;
    size_t length;

    void allocate_and_copy(const char* s, size_t len) {
        length = len;
        data = new char[length + 1];
        std::memcpy(data, s, length);
        data[length] = '\0';
    }

public:
    str() : data(nullptr), length(0) {}

    str(const char &c) : length(1) {
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    }

    str(const char *&& s_) {
        if (s_ == nullptr) {
            data = nullptr;
            length = 0;
         else {
            size_t len = std::strlen(s_);
            allocate_and_copy(s_, len);
        }
    }

    str &operator=(const char *&& s_) {
        if (data != nullptr) {
            delete[] data;
        }

        if (s_ == nullptr) {
            data = nullptr;
            length = 0;
         else {
            size_t len = std::strlen(s_);
            allocate_and_copy(s_, len);
        }

        return *this;
    }

    str(const str &other) {
        if (other.data == nullptr) {
            data = nullptr;
            length = 0;
         else {
            allocate_and_copy(other.data, other.length);
        }
    }

    str &operator=(const str &other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }

            if (other.data == nullptr) {
                data = nullptr;
                length = 0;
             else {
                allocate_and_copy(other.data, other.length);
            }
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) {
            return str();
        }

        // Calculate total length needed
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].length;
            if (i < strs.size() - 1) {
                total_len += length;  // Add separator length
            }
        }

        // Create result string
        str result;
        result.length = total_len;
        result.data = new char[total_len + 1];

        char* ptr = result.data;
        for (size_t i = 0; i < strs.size(); ++i) {
            // Copy current string
            std::memcpy(ptr, strs[i].data, strs[i].length);
            ptr += strs[i].length;

            // Add separator if not the last string
            if (i < strs.size() - 1) {
                std::memcpy(ptr, data, length);
                ptr += length;
            }
        }

        result.data[total_len] = '\0';
        return result;
    }

    str slice(size_t l, size_t r) const {
        // Clamp r to length if it's beyond the string length
        if (r > length) {
            r = length;
        }

        // Handle invalid range
        if (l >= r) {
            return str();
        }

        str result;
        result.length = r - l;
        result.data = new char[result.length + 1];
        std::memcpy(result.data, data + l, result.length);
        result.data[result.length] = '\0';

        return result;
    }

    ~str() {
        if (data != nullptr) {
            delete[] data;
        }
    }
};
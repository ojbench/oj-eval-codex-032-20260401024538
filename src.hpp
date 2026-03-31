// Minimal pylist implementation for OJ driver include
#ifndef SRC_HPP
#define SRC_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>

class pylist {
private:
    enum class Kind { LIST, INT } kind_ = Kind::LIST;
    std::shared_ptr<std::vector<pylist>> list_;
    long long ivalue_ = 0;

    void ensure_list() {
        if (kind_ != Kind::LIST) {
            kind_ = Kind::LIST;
            list_ = std::make_shared<std::vector<pylist>>();
        } else if (!list_) {
            list_ = std::make_shared<std::vector<pylist>>();
        }
    }

public:
    // Constructors
    pylist() : kind_(Kind::LIST), list_(std::make_shared<std::vector<pylist>>()), ivalue_(0) {}
    pylist(int v) : kind_(Kind::INT), list_(nullptr), ivalue_(v) {}

    // Append operations (O(1) amortized)
    void append(const pylist &x) {
        ensure_list();
        list_->push_back(x);
    }
    void append(int v) {
        ensure_list();
        list_->push_back(pylist(v));
    }

    // Pop last element (O(1))
    pylist pop() {
        ensure_list();
        if (list_->empty()) {
            return pylist();
        }
        pylist back = list_->back();
        list_->pop_back();
        return back;
    }

    // Indexing (O(1))
    pylist &operator[](std::size_t i) {
        ensure_list();
        return (*list_)[i];
    }
    const pylist &operator[](std::size_t i) const {
        // For const contexts; assumes valid access in tests
        return (*list_)[i];
    }

    // Implicit conversion to int for arithmetic contexts
    operator int() const {
        return static_cast<int>(ivalue_);
    }

    // Stream output
    friend std::ostream &operator<<(std::ostream &os, const pylist &ls) {
        if (ls.kind_ == Kind::INT) {
            os << ls.ivalue_;
            return os;
        }
        // List printing: [elem0, elem1, ...]
        os << '[';
        if (ls.list_) {
            for (std::size_t i = 0; i < ls.list_->size(); ++i) {
                if (i) os << ", ";
                os << (*ls.list_)[i];
            }
        }
        os << ']';
        return os;
    }
};

#endif // SRC_HPP

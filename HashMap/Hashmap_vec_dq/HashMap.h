#include <vector>
#include <deque>
#include <algorithm>
#include <functional>
#include <stdexcept>

template<typename KeyType, typename ValueType>
class HashMap {
public:
    using KeyValuePair = std::pair<const KeyType, ValueType>;

    HashMap(size_t max_buckets, std::function<size_t(const KeyType&)> hash_func)
        : max_buckets_(max_buckets), hash_func_(hash_func) {
        if (max_buckets_ == 0) {
            throw std::invalid_argument("Maximum number of buckets must be positive");
        }
        buckets_.resize(max_buckets_);
    }

    void put(const KeyType& key, const ValueType& value) {
        size_t bucket_idx = hash_func_(key) % max_buckets_;
        auto& bucket = buckets_[bucket_idx];
        auto it = std::find_if(bucket.begin(), bucket.end(),
                               [&key](const auto& kv) { return kv.first == key; });
        if (it != bucket.end()) {
            it->second = value;
        } else {
            bucket.emplace_back(key, value);
        }
    }

    bool get(const KeyType& key, ValueType& value, size_t& item_idx, size_t& bucket_idx) const {
        bucket_idx = hash_func_(key) % max_buckets_;
        const auto& bucket = buckets_[bucket_idx];
        auto it = std::find_if(bucket.begin(), bucket.end(),
                               [&key](const auto& kv) { return kv.first == key; });
        if (it != bucket.end()) {
            value = it->second;
            item_idx = std::distance(bucket.begin(), it);
            return true;
        } else {
            return false;
        }
    }

    size_t size() const {
        size_t count = 0;
        for (const auto& bucket : buckets_) {
            count += bucket.size();
        }
        return count;
    }

private:
    size_t max_buckets_;
    std::function<size_t(const KeyType&)> hash_func_;
    std::vector<std::deque<KeyValuePair>> buckets_;
};
int currentTime, mxCap;
map <int, int> value;
map <int, int> lastTimeAccessed;
set <pair<int, int>> timeKey;

LRUCache::LRUCache(int capacity) {
    mxCap = capacity;
    currentTime = 0;
    value.clear();
    lastTimeAccessed.clear();
    timeKey.clear();
}

void updateDS(int key){
    int last_time = lastTimeAccessed[key];
    lastTimeAccessed[key] = currentTime;
    
    timeKey.erase({last_time, key});
    timeKey.insert({currentTime, key});
    
    currentTime++;
}

int LRUCache::get(int key) {
    if(value.count(key) == 0) 
        return -1;
    updateDS(key);
    return value[key];
}

void LRUCache::set(int key, int val) {
    if(value.count(key) == 1){
        value[key] = val;
        updateDS(key);
    }
    else{
        if(value.size() == mxCap){
            // delete the lru key
            int lruKey = timeKey.begin()->second;
            lastTimeAccessed.erase(lruKey);
            timeKey.erase(*timeKey.begin());
            value.erase(lruKey);
        }
        value[key] = val;
        lastTimeAccessed[key] = currentTime;
        timeKey.insert({currentTime, key});
        currentTime++;
    }    
}
#include <iostream>
#include <map>
#include <string>
#include<vector>

std::string uidToStr(std::int64_t uid) { return std::to_string(uid); }
std::string tidToStr(std::int32_t tid) { return std::to_string(tid); }

class CItem {
 public:
  CItem(std::int64_t uid, std::int32_t tid, std::string name,
        std::int64_t count, std::int8_t type, std::int8_t subtype)
      : m_uid(uid),
        m_tid(tid),
        m_name(std::move(name)),
        m_count(count),
        m_type(type),
        m_subtype(subtype) {}

  // 对外提供的接口
  std::int64_t GetUID() const { return m_uid; }
  std::int32_t GetTID() const { return m_tid; }
  const std::string& GetName() const { return m_name; }
  std::int64_t GetCount() const { return m_count; }
  std::int8_t GetType() const { return m_type; }
  std::int8_t GetSubtype() const { return m_subtype; }
  void SetCount(std::int64_t count) { m_count = count; }

 private:
  std::int64_t m_uid;
  std::int32_t m_tid;
  std::string m_name;
  std::int64_t m_count;
  std::int8_t m_type;
  std::int8_t m_subtype;
};

class CItemMgr {
 public:
  CItemMgr() = default;
  ~CItemMgr() { Clear(); }

  // 加载物品数据
  bool LoadFromDB(const std::string& strData) {
    std::vector<std::string> vecItems;
    SplitString(strData, '|', vecItems);
    for (const auto& itemStr : vecItems) {
      std::vector<std::string> vecFields;
      SplitString(itemStr, ',', vecFields);
      if (vecFields.size() != 6) {
        std::cerr << "Invalid item data: " << itemStr << std::endl;
        continue;
      }
      try {
        std::int64_t uid = std::stoll(vecFields[0]);
        std::int32_t tid = std::stoi(vecFields[1]);
        std::string name = vecFields[2];
        std::int64_t count = std::stoll(vecFields[3]);
        std::int8_t type = static_cast<std::int8_t>(std::stoi(vecFields[4]));
        std::int8_t subtype = static_cast<std::int8_t>(std::stoi(vecFields[5]));
        m_items.emplace(uid, CItem(uid, tid, std::move(name), count, type, subtype));
      } catch (const std::exception& ex) {
        std::cerr << "Exception while parsing item data: " << ex.what() << std::endl;
        continue;
      }
    }
    return true;
  }

  // 将物品数据保存到字符串
  std::string SaveDB() const {
    std::string strData;
    for (const auto& [uid, pItem] : m_items) {
      strData += uidToStr(uid) + "," + tidToStr(pItem.GetTID()) + "," +
                 pItem.GetName() + "," + std::to_string(pItem.GetCount()) + "," +
                 std::to_string(pItem.GetType()) + "," + std::to_string(pItem.GetSubtype()) + "|";
    }
    if (!strData.empty()) {
      strData.pop_back();  // 去掉最后一个分隔符
    }
    return strData;
  }

  // 根据唯一ID查找物品对象，返回nullptr表示没找到
  CItem* FindItemByUID(std::int64_t uid) {
    auto it = m_items.find(uid);
    if (it == m_items.end()) {
      return nullptr;
    }
    return &it->second;
  }

  // 根据模板ID查找物品对象，返回nullptr表示没找到
  CItem* FindItemByTID(std::int32_t tid) {
    for (auto& [uid, item] : m_items) {
      if (item.GetTID() == tid) {
        return &item;
      }
    }
    return nullptr;
  }

  // 添加指定模板ID的物品到管理器，返回添加的物品对象指针
  CItem* AddItemByTID(std::int32_t tid, std::int64_t count = 1) {
    // 生成一个唯一ID
    std::int64_t uid = ++m_maxUID;
    // 创建物品对象并添加到管理器中
    auto [it, success] = m_items.emplace(uid, CItem(uid, tid, "", count, 0, 0));
    if (!success) {
      std::cerr << "Failed to add item, uid=" << uid << ", tid=" << tid << std::endl;
      return nullptr;
    }
    return &it->second;
  }

  // 判断指定模板ID的物品数量是否达到指定值
  bool HasItemCount(std::int32_t tid, std::int64_t count) const {
    for (const auto& [uid, item] : m_items) {
      if (item.GetTID() == tid && item.GetCount() >= count) {
        return true;
      }
    }
    return false;
  }

  // 删除指定UID的物品，返回删除的数量
  std::int64_t RemoveItem(std::int64_t uid, std::int64_t count = -1) {
    auto it = m_items.find(uid);
    if (it == m_items.end()) {
      return 0;
    }
    auto& item = it->second;
    std::int64_t removeCount = (count < 0 || count > item.GetCount()) ? item.GetCount() : count;
    item.SetCount(item.GetCount() - removeCount);
    if (item.GetCount() <= 0) {
      m_items.erase(it);
    }
    return removeCount;
  }

 private:
  void SplitString(const std::string& str, char delimiter,
                   std::vector<std::string>& result) const {
    result.clear();
    std::size_t start = 0;
    while (true) {
      std::size_t end = str.find(delimiter, start);
      if (end == std::string::npos) {
        result.emplace_back(str.substr(start));
        break;
      } else {
        result.emplace_back(str.substr(start, end - start));
        start = end + 1;
      }
    }
  }

  // 物品管理器内部维护的物品对象映射表
  std::map<std::int64_t, CItem> m_items;
  // 当前最大的唯一ID，用于生成新物品对象的UID
  std::int64_t m_maxUID = 0;

  // 清空物品管理器中的所有物品
  void Clear() { m_items.clear(); }
};

int main() {
  // 测试代码
  CItemMgr mgr;
  mgr.AddItemByTID(1001);
  mgr.AddItemByTID(1002);
  mgr.AddItemByTID(1003);
  mgr.FindItemByTID(1002)->SetCount(10);
  std::cout << "Before save: " << mgr.SaveDB() << std::endl;
  mgr.RemoveItem(1);
  std::cout << "After remove: " << mgr.SaveDB() << std::endl;
  return 0;
}

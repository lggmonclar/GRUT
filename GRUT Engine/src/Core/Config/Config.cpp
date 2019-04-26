#include "grutpch.h"
#include "Config.h"
#include "ICVar.h"
#include "Core/FileSystem.h"

namespace GRUT {
  void Config::Read(const char* p_filePath) {
    std::string contents = FileSystem::LoadFileContents(p_filePath);
    if (contents.empty())
      return;

    ProcessContents(contents);
  }

  void Config::ProcessContents(const std::string& p_contentBuffer) {
    char* nextToken;
    char* currLine = strtok_s(const_cast<char*>(p_contentBuffer.c_str()), "\n\r", &nextToken);
    while (currLine != NULL) {
      std::string line(currLine);
      RemoveComments(&line);
      if (IsOnlyWhitespace(line) || !IsValidLine(line)) {
        currLine = strtok_s(NULL, "\n", &nextToken);
        continue;
      }
      Size sepPos = line.find('=');
      std::string key, value;
      ExtractKey(&key, sepPos, line);
      ExtractValue(&value, sepPos, line);
      SetVal(key, value);
      currLine = strtok_s(NULL, "\n", &nextToken);
    }
  }

  void Config::RemoveComments(std::string* p_line) const {
    auto it = p_line->find(';');
    if (it != std::string::npos) {
      p_line->erase(it);
    }
  }

  bool Config::IsOnlyWhitespace(const std::string_view& p_line) const {
    return (p_line.find_first_not_of(' ') == std::string::npos);
  }

  bool Config::IsValidLine(const std::string_view& p_line) const {
    std::string tmp = p_line.data();
    tmp.erase(0, tmp.find_first_not_of("\t "));
    if (tmp[0] == '=') {
      return false;
    }

    auto size = tmp.length();
    for (Size i = tmp.find('=') + 1; i < size; i++) {
      if (tmp[i] != ' ') {
        return true;
      }
    }

    return false;
  }

  void Config::ExtractKey(std::string* p_key, const Size& p_sepPos, const std::string_view p_line) {
    *p_key = p_line.substr(0, p_sepPos);
    Size pos = p_key->find_first_of("\t ");
    if (pos != std::string::npos) {
      p_key->erase(pos);
    }
  }

  void Config::ExtractValue(std::string* p_value, const Size& p_sepPos, const std::string_view p_line) {
    *p_value = p_line.substr(p_sepPos + 1);
    p_value->erase(0, p_value->find_first_not_of("\t "));
    p_value->erase(p_value->find_last_not_of("\t ") + 1);
  }

  void Config::SetVal(const std::string& p_key, const std::string_view& p_value) {
    //StringId keySid = SID(p_key.c_str());
    //ICVar* cvar = m_registry.Find(keySid);
    //if (cvar != nullptr) {
    //  cvar->SetVal(p_value.data());
    //}
  }
}
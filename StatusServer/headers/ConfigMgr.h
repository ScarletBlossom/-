#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <map>
#include <string>


struct SectionInfo{
    SectionInfo(){}
    ~SectionInfo();
    SectionInfo(const SectionInfo& src);
    SectionInfo& operator=(const SectionInfo& src);
    std::map<std::string,std::string> _section_datas;
    std::string operator[](const std::string key);
};

class ConfigMgr{
public:
    ~ConfigMgr();
    ConfigMgr(const ConfigMgr&) = delete;
    ConfigMgr operator=(const ConfigMgr&) = delete;
    SectionInfo operator[](const std::string &key);
    static ConfigMgr& GetInstance();
private:
    ConfigMgr();
    std::map<std::string,SectionInfo> _config_map; 

};

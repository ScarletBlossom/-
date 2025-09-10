#include "../headers/ConfigMgr.h"
#include <boost/filesystem.hpp>
#include <iostream>

SectionInfo::~SectionInfo(){
    _section_datas.clear();
}

SectionInfo::SectionInfo(const SectionInfo& src){
    _section_datas = src._section_datas;
}

SectionInfo& SectionInfo::operator=(const SectionInfo& src){
    if(&src==this){
        return *this;
    }
    _section_datas = src._section_datas;
    return *this;
}

std::string SectionInfo::operator[](const std::string key){
    if(_section_datas.find(key)==_section_datas.end()){
        return "";
    }
    return _section_datas[key];
}

ConfigMgr::ConfigMgr(){
    // 获取当前工作目录  
    boost::filesystem::path current_path = boost::filesystem::current_path();
    // 构建config.ini文件的完整路径  
    boost::filesystem::path config_path = current_path / ".." / "ini/config.ini";
    std::cout << "Config path: " << config_path << std::endl;

    // 使用Boost.PropertyTree来读取INI文件  
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config_path.string(), pt);
    
    for (const auto& section_pair : pt) {
        const std::string& section_name = section_pair.first;
        const boost::property_tree::ptree& section_tree = section_pair.second;

        // 对于每个section，遍历其所有的key-value对  
        std::map<std::string, std::string> section_config;
        for (const auto& key_value_pair : section_tree) {
            const std::string& key = key_value_pair.first;
            const std::string& value = key_value_pair.second.get_value<std::string>();
            section_config[key] = value;
        }
        SectionInfo sectionInfo;
        sectionInfo._section_datas = section_config;
        // 将section的key-value对保存到config_map中  
        _config_map[section_name] = sectionInfo;
    }

}

ConfigMgr& ConfigMgr::GetInstance(){
    static ConfigMgr instance;
    return instance;
}
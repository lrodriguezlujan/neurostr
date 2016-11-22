#include <neurostr/io/parser_dispatcher.h>

namespace neurostr {
namespace io{
  
  Parser* get_parser_by_ext(const std::string& s, std::istream& stream){
  
    std::string ext(s); // copy
    
    // Convert to lowercase
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    if(ext == "swc"){
      return new io::SWCParser(stream);
    } else if (ext == "asc"){
      return new io::ASCParser(stream);
    } else if (ext == "dat"){
      return new io::DATParser(stream);
    } else if (ext == "json"){
      return new io::JSONParser(stream);
    } else {
      //Errror
      throw std::runtime_error("Unrecognized type");
     }
  }
  
  void open_filestream(const std::string& path, const std::string& s, std::ifstream& ret) {
    std::string ext(s); // copy
    // Convert to lowercase
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "dat"){
      ret.open(path, std::ios_base::binary);
    } else {
      ret.open(path);
    }
  }
  
  std::unique_ptr<Reconstruction> read_file_by_ext(const std::string& path){
    // Create path
    boost::filesystem::path fspath(path);
  
    // Extract extension
    std::string extension = fspath.extension().string<std::string>().erase(0,1);
    std::string name      = fspath.stem().string<std::string>();
    
    std::ifstream in;
    open_filestream(path,extension,in);
    
    Parser* p = get_parser_by_ext(extension,in);
    auto ret = p->read(name);
    in.close();
    delete p;
    
    return ret;
  }
  
}//io
}//neurostr

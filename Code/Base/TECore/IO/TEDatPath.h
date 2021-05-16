#ifndef TEDATPATH_H
#define TEDATPATH_H

#include <string>

namespace TE {
namespace IO {
    class DatPath {
      public:
        explicit DatPath(const std::string &path);

        bool operator<(const DatPath &other) const {
            return m_path < other.m_path;
        }

        bool operator==(const DatPath &other) const {
            return m_path == other.m_path;
        }

        bool IsFile() const;
        bool IsFolder() const;
        bool IsRoot() const;
        bool IsValid() const;
        bool InSubPathOf(const DatPath &datPath);
        bool InSubPathOfRecursive(const DatPath &datPath);
        void CdUp();
        void Cd(const std::string &folder);
        const std::string &GetFullPath() const;

        /*    Gets the name of the folder or file under the relative path eg:
         *	  If path is "/In/Some/Folder/There/a/file.tmp" and path of datPath is
         *	  "/In/Some/" the returned will be "Folder". If the datPath is
         *    "/In/Some/Folder/There/a/" the returned will be "file.tmp"
         */
        const std::string GetFolderIn(const DatPath &datPath) const;
        const std::string GetFileOrFolder();

      private:
        std::string m_path;
        static std::string m_validChars;
    };
}
}

#endif
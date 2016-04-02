namespace tes_api_3 {

    using namespace collections;

    class tes_jcontainers : public class_meta<tes_jcontainers> {
    public:

        REGISTER_TES_NAME("JContainers");

        void additionalSetup() {
            metaInfo.comment = "Various utility methods";
        }

        static bool __isInstalled() {
            return true;
        }
        REGISTERF2_STATELESS(__isInstalled, nullptr, "NOT part of public API");

        static UInt32 APIVersion() {
            return (UInt32)consts::api_version;
        }
        REGISTERF2_STATELESS(APIVersion, nullptr, []() {
            std::stringstream comm;
            comm << "Version information.\n"
                "It's a good practice to validate installed JContainers version with the following code:\n"
                "    bool isJCValid = JContainers.APIVersion() == AV && JContainers.featureVersion() >= FV\n"
                "where AV and FV are hardcoded API and feature version numbers.\n";
            comm << "Current API version is " << APIVersion() << std::endl;
            comm << "Current feature version is " << featureVersion();
            return comm.str();
        });

        static UInt32 featureVersion() {
            return (UInt32)consts::feature_version;
        }
        REGISTERF2_STATELESS(featureVersion, nullptr, nullptr);

        static bool fileExistsAtPath(const char *filename) {
            if (!filename) {
                return false;
            }

            struct _stat buf;
            int result = _stat(filename, &buf);
            return result == 0;
        }
        REGISTERF2_STATELESS(fileExistsAtPath, "path", "Returns true if file at a specified path exists");

        static void removeFileAtPath(const char *filename) {
            if (filename) {
                boost::filesystem::remove_all(filename);
            }
        }
        REGISTERF2_STATELESS(removeFileAtPath, "path", "Deletes the file or directory identified by a given path");

        static std::string userDirectory() {
            char path[MAX_PATH];
            if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, path))) {
                return std::string();
            }

            strcat_s(path, sizeof(path), "/" JC_USER_FILES);

            // race condition possible. hope it's not critical
            if (!boost::filesystem::exists(path) && (boost::filesystem::create_directories(path), !boost::filesystem::exists(path))) {
                return std::string();
            }

            return path;
        }

        static skse::string_ref _userDirectory() {
            return userDirectory().c_str();
        }
        REGISTERF_STATELESS(_userDirectory, "userDirectory", "", "A path to user-specific directory - "JC_USER_FILES);

        static SInt32 lastError() {
            return 0;
        }
        REGISTERF2_STATELESS(lastError, nullptr, []() {
            std::stringstream comm;
            comm << "DEPRECATE. Returns last occured error (error code):";
            for (int i = 0; i < JErrorCount; ++i) {
               comm << std::endl << i << " - " << JErrorCodeToString((JErrorCode)i);
            }
            return comm.str();
        });

        static skse::string_ref lastErrorString() {
            return "";
        }
        REGISTERF2_STATELESS(lastErrorString, nullptr, "DEPRECATE. Returns string that describes last error");

        REGISTER_TEXT([]() {
            const char* fmt = R"===(
; Returns true if JContainers plugin installed properly
bool function isInstalled() global
    return __isInstalled() && %u == APIVersion() && %u == featureVersion()
endfunction
)===";
            char buff[1024] = { 0 };
            assert(-1 != sprintf_s(buff, fmt, consts::api_version, consts::feature_version));
            return std::string(buff);
        });
    };

    TES_META_INFO(tes_jcontainers);

    TEST(tes_jcontainers, userDirectory)
    {
        tes_context ctx;

        auto write_file = [&](const boost::filesystem::path& path) {
            boost::filesystem::remove_all(path);

            EXPECT_FALSE(boost::filesystem::is_regular(path));

            object_stack_ref obj = tes_object::object<map>(ctx);
            tes_object::writeToFile(ctx, obj.get(), path.string().c_str());

            EXPECT_TRUE(boost::filesystem::is_regular(path));

            boost::filesystem::remove_all(path);
        };

        auto path = tes_jcontainers::userDirectory();
        EXPECT_TRUE(!path.empty());
        EXPECT_TRUE(boost::filesystem::is_directory(path));

        write_file(tes_jcontainers::userDirectory() + "/MyMod/123/settings.json");
        write_file(tes_jcontainers::userDirectory() + "/settings.json");
        write_file(tes_jcontainers::userDirectory() + "settings2.json");
        write_file("obj3");
        write_file("path/obj3");
        write_file("/path2/obj3");
        write_file("path3\\obj3");
        write_file("\\path4\\obj3");
    }
}

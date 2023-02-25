#ifndef LAZY_IMPORTER_HPP
#define LAZY_IMPORTER_HPP

#define LI_FN(name) ::li::detail::lazy_function<LAZY_IMPORTER_KHASH(#name), decltype(&name)>()

#include <utility>
#include <intrin.h>

#define LAZY_IMPORTER_STRINGIZE(x) #x
#define LAZY_IMPORTER_STRINGIZE_EXPAND(x) LAZY_IMPORTER_STRINGIZE(x)

#define LAZY_IMPORTER_KHASH(str) ::li::detail::khash(str, \
    ::li::detail::khash_impl( __TIME__ __DATE__ LAZY_IMPORTER_STRINGIZE_EXPAND(__LINE__) LAZY_IMPORTER_STRINGIZE_EXPAND(__COUNTER__), 2166136261 ))

namespace li { namespace detail {

    namespace win {
        struct IMAGE_DOS_HEADER { // DOS .EXE header
            unsigned short e_magic; // Magic number
            unsigned short e_cblp; // Bytes on last page of file
            unsigned short e_cp; // Pages in file
            unsigned short e_crlc; // Relocations
            unsigned short e_cparhdr; // Size of header in paragraphs
            unsigned short e_minalloc; // Minimum extra paragraphs needed
            unsigned short e_maxalloc; // Maximum extra paragraphs needed
            unsigned short e_ss; // Initial (relative) SS value
            unsigned short e_sp; // Initial SP value
            unsigned short e_csum; // Checksum
            unsigned short e_ip; // Initial IP value
            unsigned short e_cs; // Initial (relative) CS value
            unsigned short e_lfarlc; // File address of relocation table
            unsigned short e_ovno; // Overlay number
            unsigned short e_res[4]; // Reserved words
            unsigned short e_oemid; // OEM identifier (for e_oeminfo)
            unsigned short e_oeminfo; // OEM information; e_oemid specific
            unsigned short e_res2[10]; // Reserved words
            long           e_lfanew; // File address of new exe header
        };

        struct IMAGE_FILE_HEADER {
            unsigned short Machine;
            unsigned short NumberOfSections;
            unsigned long  TimeDateStamp;
            unsigned long  PointerToSymbolTable;
            unsigned long  NumberOfSymbols;
            unsigned short SizeOfOptionalHeader;
            unsigned short Characteristics;
        };

        struct IMAGE_EXPORT_DIRECTORY {
            unsigned long  Characteristics;
            unsigned long  TimeDateStamp;
            unsigned short MajorVersion;
            unsigned short MinorVersion;
            unsigned long  Name;
            unsigned long  Base;
            unsigned long  NumberOfFunctions;
            unsigned long  NumberOfNames;
            unsigned long  AddressOfFunctions; // RVA from base of image
            unsigned long  AddressOfNames; // RVA from base of image
            unsigned long  AddressOfNameOrdinals; // RVA from base of image
        };

        struct IMAGE_DATA_DIRECTORY {
            unsigned long VirtualAddress;
            unsigned long Size;
        };

        struct IMAGE_OPTIONAL_HEADER64 {
            unsigned short       Magic;
            unsigned char        MajorLinkerVersion;
            unsigned char        MinorLinkerVersion;
            unsigned long        SizeOfCode;
            unsigned long        SizeOfInitializedData;
            unsigned long        SizeOfUninitializedData;
            unsigned long        AddressOfEntryPoint;
            unsigned long        BaseOfCode;
            unsigned long long   ImageBase;
            unsigned long        SectionAlignment;
            unsigned long        FileAlignment;
            unsigned short       MajorOperatingSystemVersion;
            unsigned short       MinorOperatingSystemVersion;
            unsigned short       MajorImageVersion;
            unsigned short       MinorImageVersion;
            unsigned short       MajorSubsystemVersion;
            unsigned short       MinorSubsystemVersion;
            unsigned long        Win32VersionValue;
            unsigned long        SizeOfImage;
            unsigned long        SizeOfHeaders;
            unsigned long        CheckSum;
            unsigned short       Subsystem;
            unsigned short       DllCharacteristics;
            unsigned long long   SizeOfStackReserve;
            unsigned long long   SizeOfStackCommit;
            unsigned long long   SizeOfHeapReserve;
            unsigned long long   SizeOfHeapCommit;
            unsigned long        LoaderFlags;
            unsigned long        NumberOfRvaAndSizes;
            IMAGE_DATA_DIRECTORY DataDirectory[16];
        };

        struct IMAGE_OPTIONAL_HEADER32 {
            unsigned short       Magic;
            unsigned char        MajorLinkerVersion;
            unsigned char        MinorLinkerVersion;
            unsigned long        SizeOfCode;
            unsigned long        SizeOfInitializedData;
            unsigned long        SizeOfUninitializedData;
            unsigned long        AddressOfEntryPoint;
            unsigned long        BaseOfCode;
            unsigned long        BaseOfData;
            unsigned long        ImageBase;
            unsigned long        SectionAlignment;
            unsigned long        FileAlignment;
            unsigned short       MajorOperatingSystemVersion;
            unsigned short       MinorOperatingSystemVersion;
            unsigned short       MajorImageVersion;
            unsigned short       MinorImageVersion;
            unsigned short       MajorSubsystemVersion;
            unsigned short       MinorSubsystemVersion;
            unsigned long        Win32VersionValue;
            unsigned long        SizeOfImage;
            unsigned long        SizeOfHeaders;
            unsigned long        CheckSum;
            unsigned short       Subsystem;
            unsigned short       DllCharacteristics;
            unsigned long        SizeOfStackReserve;
            unsigned long        SizeOfStackCommit;
            unsigned long        SizeOfHeapReserve;
            unsigned long        SizeOfHeapCommit;
            unsigned long        LoaderFlags;
            unsigned long        NumberOfRvaAndSizes;
            IMAGE_DATA_DIRECTORY DataDirectory[16];
        };

        struct IMAGE_NT_HEADERS {
            unsigned long     Signature;
            IMAGE_FILE_HEADER FileHeader;
#ifdef _WIN64
            IMAGE_OPTIONAL_HEADER64 OptionalHeader;
#else
            IMAGE_OPTIONAL_HEADER32 OptionalHeader;
#endif
        };

    } // namespace win

    struct forwarded_hashes {
       unsigned module_hash;
       unsigned function_hash;
    };

    // 64 bit integer where 32 bits are used for the hash offset
    // and remaining 32 bits are used for the hash computed using it
    using offset_hash_pair = unsigned long long;

    __forceinline constexpr unsigned get_hash(offset_hash_pair pair) noexcept { return ( pair & 0xFFFFFFFF ); }

    __forceinline constexpr unsigned get_offset(offset_hash_pair pair) noexcept { return ( pair >> 32 ); }

    template<bool CaseSensitive = true>
    __forceinline constexpr unsigned hash_single(unsigned value, char c) noexcept
    {
        return static_cast<unsigned int>(
            (value ^ ((!CaseSensitive && c >= 'A' && c <= 'Z') ? (c | (1 << 5)) : c)) *
            static_cast<unsigned long long>(16777619));
    }

    __forceinline constexpr unsigned
        khash_impl(const char* str, unsigned value) noexcept
    {
        return (*str ? khash_impl(str + 1, hash_single(value, *str)) : value);
    }

    __forceinline constexpr offset_hash_pair khash(
        const char* str, unsigned offset) noexcept
    {
        return ((offset_hash_pair{ offset } << 32) | khash_impl(str, offset));
    }

    template<class CharT = char>
    __forceinline unsigned hash(const CharT* str, unsigned offset) noexcept
    {
        unsigned value = offset;

        for(;;) {
            char c = *str++;
            if(!c)
                return value;
            value = hash_single(value, c);
        }
    }

    __forceinline forwarded_hashes hash_forwarded(
        const char* str, unsigned offset) noexcept
    {
        forwarded_hashes res{ offset, offset };

        for(; *str != '.'; ++str)
            res.module_hash = hash_single<true>(res.module_hash, *str);

        ++str;

        for(; *str; ++str)
            res.function_hash = hash_single(res.function_hash, *str);

        return res;
    }

    __forceinline const win::IMAGE_NT_HEADERS* nt_headers(
        const char* base) noexcept
    {
        return reinterpret_cast<const win::IMAGE_NT_HEADERS*>(
            base + reinterpret_cast<const win::IMAGE_DOS_HEADER*>(base)->e_lfanew);
    }

    __forceinline const win::IMAGE_EXPORT_DIRECTORY* image_export_dir(
        const char* base) noexcept
    {
        return reinterpret_cast<const win::IMAGE_EXPORT_DIRECTORY*>(
            base + nt_headers(base)->OptionalHeader.DataDirectory->VirtualAddress);
    }

    struct exports_directory {
        const char*                        _base;
        const win::IMAGE_EXPORT_DIRECTORY* _ied;
        unsigned long                      _ied_size;

    public:
        using size_type = unsigned long;

        __forceinline
        exports_directory(const char* base) noexcept : _base(base)
        {
            const auto ied_data_dir = nt_headers(base)->OptionalHeader.DataDirectory[0];
            _ied = reinterpret_cast<const win::IMAGE_EXPORT_DIRECTORY*>(
                base + ied_data_dir.VirtualAddress);
            _ied_size = ied_data_dir.Size;
        }

        __forceinline explicit operator bool() const noexcept
        {
            return reinterpret_cast<const char*>(_ied) != _base;
        }

        __forceinline size_type size() const noexcept
        {
            return _ied->NumberOfNames;
        }

        __forceinline const char* base() const noexcept { return _base; }
        __forceinline const win::IMAGE_EXPORT_DIRECTORY* ied() const noexcept
        {
            return _ied;
        }

        __forceinline const char* name(size_type index) const noexcept
        {
            return reinterpret_cast<const char*>(
                _base + reinterpret_cast<const unsigned long*>(
                            _base + _ied->AddressOfNames)[index]);
        }

        __forceinline const char* address(size_type index) const noexcept
        {
            const auto* const rva_table =
                reinterpret_cast<const unsigned long*>(_base + _ied->AddressOfFunctions);

            const auto* const ord_table = reinterpret_cast<const unsigned short*>(
                _base + _ied->AddressOfNameOrdinals);

            return _base + rva_table[ord_table[index]];
        }

        __forceinline bool is_forwarded(
            const char* export_address) const noexcept
        {
            const auto ui_ied = reinterpret_cast<const char*>(_ied);
            return (export_address > ui_ied && export_address < ui_ied + _ied_size);
        }
    };

    extern "C" unsigned long long ntoskrnl_base;
    __forceinline const unsigned long long ntos() noexcept
    {
        return ntoskrnl_base;
    }

    // provides the cached functions which use Derive classes methods
    template<class Derived, class DefaultType = void*>
    class lazy_base {
    protected:
        // This function is needed because every templated function
        // with different args has its own static buffer
        __forceinline static void*& _cache() noexcept
        {
            static void* value = nullptr;
            return value;
        }

    public:
        template<class T = DefaultType>
        __forceinline static T safe() noexcept
        {
            return Derived::template get<T>();
        }

        template<class T = DefaultType>
        __forceinline static T cached() noexcept
        {
            auto& cached = _cache();
            if(!cached)
                cached = Derived::template get<void*>();

            return (T)(cached);
        }

        template<class T = DefaultType>
        __forceinline static T safe_cached() noexcept
        {
            return cached<T>();
        }
    };

    template<offset_hash_pair OHP, class T>
    struct lazy_function : lazy_base<lazy_function<OHP, T>, T> {
        using base_type = lazy_base<lazy_function<OHP, T>, T>;

        template<class... Args>
        __forceinline decltype(auto) operator()(Args&&... args) const
        {
            return get()(std::forward<Args>(args)...);
            
        }

        template<class F = T>
        __forceinline static F get() noexcept
        {
            const exports_directory exports(reinterpret_cast<const char*>(ntos()));
            if(exports) 
            {
                auto export_index = exports.size();
                while(export_index--)
                    if(hash(exports.name(export_index), get_offset(OHP)) == get_hash(OHP))
                        return (F)(exports.address(export_index));
            }
            return {};
        }
    };

}} // namespace li::detail

#endif // include guard
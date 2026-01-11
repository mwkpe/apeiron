#ifndef APEIRON_UTILITY_DPI_SCALING_H
#define APEIRON_UTILITY_DPI_SCALING_H


#include <memory>

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#endif


namespace apeiron::utility {


void disable_dpi_scaling()
{
  // Silence gcc >= 8 warning about the winapi function cast
  #ifdef _WIN32
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-function-type"

    enum { PROCESS_DPI_UNAWARE, PROCESS_SYSTEM_DPI_AWARE, PROCESS_PER_MONITOR_DPI_AWARE };
    auto free_module = [](HMODULE module){ FreeLibrary(module); };
    using mp = std::unique_ptr<std::remove_pointer<HMODULE>::type, decltype(free_module)>;

    if (auto shcore = mp{LoadLibrary("Shcore.dll"), free_module}) {
      using fp = HRESULT(WINAPI*)(int);

      if (auto f = reinterpret_cast<fp>(GetProcAddress(shcore.get(), "SetProcessDpiAwareness"))) {
        if (f(PROCESS_SYSTEM_DPI_AWARE) != S_OK) {
          std::cerr << "Could not disable DPI scaling" << std::endl;
        }
      }
    }

    #pragma GCC diagnostic pop
  #endif
}


}  // namespace apeiron::utility


#endif  // APEIRON_UTILITY_DPI_SCALING_H

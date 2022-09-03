import os
import shutil
import sys

import C_TO_LOGIC
import SIM
import SYN


def DO_SIM(latency, parser_state):
    print(
        "================== Doing CXXRTL Simulation ================================",
        flush=True,
    )
    CXXRTL_OUT_DIR = SYN.SYN_OUTPUT_DIRECTORY + "/cxxrtl"
    if not os.path.exists(CXXRTL_OUT_DIR):
        os.makedirs(CXXRTL_OUT_DIR)
    # Generate helpful include of cxxrtl names
    names_text = ""
    # Clocks
    clock_name_to_mhz, out_filepath = SYN.GET_CLK_TO_MHZ_AND_CONSTRAINTS_PATH(
        parser_state, None, True
    )
    if len(clock_name_to_mhz) > 1:
        print(
            "WARNING: Multiple clocks for CXXRTL probably won't work!",
            list(clock_name_to_mhz.keys()),
        )
        for clock_name, mhz in clock_name_to_mhz.items():
            if mhz:
                names_text += f'#define {clock_name} p_{clock_name.replace("_","__")}\n'
            else:
                names_text += f'#define clk p_{clock_name.replace("_","__")}\n'
    else:
        clock_name, mhz = list(clock_name_to_mhz.items())[0]
        names_text += f'#define clk p_{clock_name.replace("_","__")}\n'

    # Debug ports
    for func in parser_state.main_mhz:
        if func.endswith("_DEBUG_OUTPUT_MAIN"):
            debug_name = func.split("_DEBUG")[0]
            names_text += (
                f'#define {debug_name} p_{func.replace("_","__")}__return__output\n'
            )
    # Write names files
    names_h_path = CXXRTL_OUT_DIR + "/pipelinec_cxxrtl.h"
    f = open(names_h_path, "w")
    f.write(names_text)
    f.close()

    # Generate main.cpp
    main_cpp_text = """
// Default main.cpp template
#include <iostream>
#include "top.cpp"

// Names generated by PipelineC tool
#include "pipelinec_cxxrtl.h"
   
using namespace std;
   
int main()
{
    cxxrtl_design::p_top top;
    top.step();

    for(int cycle=0; cycle<10; ++cycle)
    {
       top.debug_eval(); // if not called, some values are optimized away

       top.clk.set<bool>(false); top.step();
       top.clk.set<bool>(true); top.step();
  
       cout << "See pipelinec_cxxrtl.h for names to use like top.NAME.get<bool>()" << endl;
    }
    return 0;
}

"""
    main_cpp_path = CXXRTL_OUT_DIR + "/" + "main.cpp"
    f = open(main_cpp_path, "w")
    f.write(main_cpp_text)
    f.close()

    # Identify tool versions
    if os.path.exists(f"{OPEN_TOOLS.GHDL_BIN_PATH}/ghdl"):
        print(
            OPEN_TOOLS.GHDL_BIN_PATH
            + "\n"
            + C_TO_LOGIC.GET_SHELL_CMD_OUTPUT(
                f"{OPEN_TOOLS.GHDL_BIN_PATH}/ghdl --version"
            ),
            flush=True,
        )
    else:
        raise Exception("ghdl executable not found!")
    if os.path.exists(f"{OPEN_TOOLS.YOSYS_BIN_PATH}/yosys"):
        print(
            OPEN_TOOLS.YOSYS_BIN_PATH
            + "\n"
            + C_TO_LOGIC.GET_SHELL_CMD_OUTPUT(
                f"{OPEN_TOOLS.YOSYS_BIN_PATH}/yosys --version"
            ),
            flush=True,
        )
    else:
        raise Exception("yosys executable not found!")

    # Generate+compile sim .cpp from output VHDL
    # Get all vhd files in syn output
    vhd_files = SIM.GET_SIM_FILES(latency=0)
    # Write a shell script to execute
    import OPEN_TOOLS

    m_ghdl = ""
    if not OPEN_TOOLS.GHDL_PLUGIN_BUILT_IN:
        m_ghdl = "-m ghdl "
    sh_text = f"""
{OPEN_TOOLS.GHDL_BIN_PATH}/ghdl -i --std=08 `cat ../vhdl_files.txt` && \
{OPEN_TOOLS.GHDL_BIN_PATH}/ghdl -m --std=08 top && \
{OPEN_TOOLS.YOSYS_BIN_PATH}/yosys -g {m_ghdl}-p "ghdl --std=08 top; write_cxxrtl ./top.cpp" && \
clang++ -g -O3 -std=c++14 -I `yosys-config --datdir`/include main.cpp -o ./top
"""
    sh_path = CXXRTL_OUT_DIR + "/" + "cxxrtl.sh"
    f = open(sh_path, "w")
    f.write(sh_text)
    f.close()

    # Run compile
    print("Compiling...", flush=True)
    bash_cmd = f"bash {sh_path}"
    # print(bash_cmd, flush=True)
    log_text = C_TO_LOGIC.GET_SHELL_CMD_OUTPUT(bash_cmd, cwd=CXXRTL_OUT_DIR)
    # print(log_text, flush=True)

    # Run the simulation
    print("Starting simulation...", flush=True)
    bash_cmd = "./top"
    # print(bash_cmd, flush=True)
    log_text = C_TO_LOGIC.GET_SHELL_CMD_OUTPUT(bash_cmd, cwd=CXXRTL_OUT_DIR)
    print(log_text, flush=True)
    sys.exit(0)

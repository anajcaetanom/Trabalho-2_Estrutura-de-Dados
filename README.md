# 🏥 Medical Examination Control Simulation in C

This project is a simulation of a medical examination control system implemented in C. It utilizes data structures such as lists and queues to manage patient arrivals, conduct X-ray examinations, and issue medical reports.

## 📂 Project Structure

The project is organized into the following files:

- **tp2.h**: Contains declarations of data structures and function prototypes used throughout the project.

- **tp2.c**: Provides implementations of the functions declared in `tp2.h`.

- **main.c**: The main program that orchestrates the simulation of medical examination control by utilizing functions implemented in `tp2.c`.

- **input.txt**: An input file used to feed data into the simulation.

- **Makefile**: Facilitates the build process of the project.

## 🚀 How to Build and Run

1. **Build the Project**:
   - Ensure that the `Makefile` is in the same directory as your source files.
   - Open a terminal in the project directory and execute:
     ```sh
     make
     ```

2. **Run the Simulation**:
   - After a successful build, run the program with:
     ```sh
     ./main
     ```

## 🔑 Key Implementation Decisions

- **Patient Arrival Simulation**: Each iteration of the loop simulates patient arrivals with a 20% probability.

- **X-ray Examination Duration**: The duration for an X-ray examination is randomly determined between 5 and 10 time units.

- **Medical Report Preparation Time**: The time taken to prepare a medical report is randomly set between 10 and 15 time units.

## 🔧 Future Enhancements

- Implement error handling for edge cases.
- Expand support for additional medical examinations.
- Develop a graphical user interface (GUI) for better user interaction.

## 📄 License

This project is open-source and can be freely modified and distributed.

---

✨ Developed in C for educational and learning purposes! 🚀

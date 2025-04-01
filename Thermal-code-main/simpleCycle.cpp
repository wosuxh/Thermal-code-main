#include<bits/stdc++.h>
using namespace std;

// Constants
const double GAMMA = 1.4;
const double Cp = 1.005; // kJ/kg.K

// Function to calculate temperature after compression
double T2_calc(double T1, double rp, double eta_c) {
    return T1 * pow(rp, (GAMMA - 1) / GAMMA / eta_c);
}

// Function to calculate temperature after expansion
double T4_calc(double T3, double rp, double eta_t) {
    return T3 * pow(1 / rp, (GAMMA - 1) / GAMMA * eta_t);
}

// Function to calculate thermal efficiency
double thermal_efficiency(double T1, double T2, double T3, double T4) {
    return 1 - ((T4 - T1) / (T3 - T2));
}

// Function to calculate overall efficiency
double overall_efficiency(double eta_th) {
    return eta_th * 100;
}

// Function to calculate power output if mass flow rate is given
double power_output(double mass_flow_rate, double T1, double T2, double T3, double T4) {
    double Wc = mass_flow_rate * Cp * (T2 - T1);
    double Wt = mass_flow_rate * Cp * (T3 - T4);
    return Wt - Wc;
}

int main() {
    double rp, T1, T3, eta_c = 1, eta_t = 1, mass_flow_rate = -1;
    
    cout << "Enter pressure ratio: ";
    cin >> rp;
    cout << "Enter inlet temperature (K): ";
    cin >> T1;
    cout << "Enter maximum cycle temperature (K): ";
    cin >> T3;
    
    cout << "Enter isentropic efficiency of compressor (default 1 if unknown): ";
    cin >> eta_c;
    cout << "Enter isentropic efficiency of turbine (default 1 if unknown): ";
    cin >> eta_t;
    cout << "Enter mass flow rate (kg/s) (default -1 if unknown): ";
    cin >> mass_flow_rate;
    
    double T2 = T2_calc(T1, rp, eta_c);
    double T4 = T4_calc(T3, rp, eta_t);
    double eta_th = thermal_efficiency(T1, T2, T3, T4);
    double eta_overall = overall_efficiency(eta_th);
    
    cout << "Overall Efficiency: " << eta_overall << " %\n";
    
    if (mass_flow_rate != -1) {
        double W_net = power_output(mass_flow_rate, T1, T2, T3, T4);
        cout << "Net Power Output: " << W_net << " kW\n";
    }
    
    return 0;
}

import matplotlib.pyplot as plt
import numpy as np

# Define the eta range and bin edges
def main():
    ppbins = np.array([
        -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, 
        -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, 
        -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, 
        -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, 
        -0.435, -0.348, -0.261, -0.174, -0.087, 
        +0.000, 
        +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
        +0.879, +0.957, +1.044, +1.131, +1.218, +1.305, +1.392, +1.479, +1.566, 
        +1.653, +1.740, +1.830, +1.930, +2.043, +2.172, +2.322, +2.500, +2.650, 
        +2.853, +2.964, +3.139, +3.314, +3.489, +3.664, +3.839, +4.013, +4.191, 
        +4.363, +4.538, +4.716, +4.889, +5.191
        ])  


    upcbins = np.array([
        -5.191, -4.889, -4.538, -3.139,   
        -2.964, -2.650,
        -2.500, -2.172, -1.740, 
        -1.305, -1.044, -0.696, -0.348,
        +0.000, 
        +0.348, +0.696, +1.044, +1.305,
        +1.740, +2.172, +2.500,
        +2.650, +2.964,
        +3.139, +4.538, +4.889, +5.191
        ])

    detector_edges = np.array([
        -5.191, -2.964, -2.500, -1.305,
        0.,
        +1.305, +2.500, +2.964, +5.191
        ])

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 4))
    for x in ppbins:
        ax1.axvline(x, color='gray', linestyle='-', alpha=0.5)
    for x in upcbins:
        ax2.axvline(x, color='gray', linestyle='-', alpha=0.5)
    for ax in [ax1, ax2]:
        ax.set_xlim(-5.191, 5.191)
        ax.set_xlabel('$\\eta$')
        ax.set_title('Default binning')
        ax.yaxis.set_visible(False)
        ax.text(-4.1, 0.5, 'HF-')
        ax.text(-3, 0.5, 'EC2-')
        ax.text(-2.1, 0.5, 'EC1-')
        ax.text(-0.8, 0.5, 'BB-')
        ax.text(0.5, 0.5, 'BB+')
        ax.text(1.7, 0.5, 'EC1+')
        ax.text(2.5, 0.5, 'EC2+')
        ax.text(3.9, 0.5, 'HF+')

    for x in detector_edges:
        ax1.axvline(x, color='black', linestyle=':', alpha=1)
        ax2.axvline(x, color='black', linestyle=':', alpha=1)
    plt.savefig("eta_bins.png")

if __name__ == "__main__":
    main()



#include<iostream>

template<typename T> 
void chompa(T v)
{
  std::cout<< v<< std::endl;
}
#include <iostream>
#include <cstring>  // For memset

// Definition of structures with hardcoded values
typedef struct {
    int32_t dimSize;
    int32_t elt[4];  // Hardcoding this array to have 4 elements
} TD2;
typedef TD2** TD2Hdl;

typedef struct {
    uint32_t ContourType;
    uint32_t ROIType;
    TD2Hdl Points;
} TD4;

typedef struct {
    int32_t dimSize;
    TD4 elt[2];  // Hardcoding this array to have 2 elements
} TD3;
typedef TD3** TD3Hdl;

typedef struct {
    TD2Hdl GlobalRectangle;
    TD3Hdl Contours;
} TD1;

typedef struct {
    int32_t dimSizes[2];
    uint8_t elt[40];  // Hardcoding this array to be 10x4 = 40 elements
} TD5;
typedef TD5** TD5Hdl;

// Function to create a TD2Hdl with hardcoded values
TD2Hdl createTD2Hdl() {
    TD2Hdl handle = new TD2*[1];
    handle[0] = new TD2;
    handle[0]->dimSize = 4;  // Hardcoding 4 elements in elt array
    handle[0]->elt[0] = 10;
    handle[0]->elt[1] = 20;
    handle[0]->elt[2] = 30;
    handle[0]->elt[3] = 40;
    return handle;
}

// Function to create a TD3Hdl with hardcoded values
TD3Hdl createTD3Hdl() {
    TD3Hdl handle = new TD3*[1];
    handle[0] = new TD3;
    handle[0]->dimSize = 2;  // Hardcoding 2 elements in elt array

    handle[0]->elt[0].ContourType = 1;
    handle[0]->elt[0].ROIType = 100;
    handle[0]->elt[0].Points = createTD2Hdl();  // Hardcoded values for points

    handle[0]->elt[1].ContourType = 2;
    handle[0]->elt[1].ROIType = 200;
    handle[0]->elt[1].Points = createTD2Hdl();  // Hardcoded values for points

    return handle;
}

// Function to create a TD1 structure with hardcoded values
TD1* createTD1() {
    TD1* handle = new TD1;
    handle->GlobalRectangle = createTD2Hdl();  // Hardcoded rectangle points
    handle->Contours = createTD3Hdl();  // Hardcoded contours
    return handle;
}

// Function to create a TD5Hdl with hardcoded values
TD5Hdl createTD5Hdl() {
    TD5Hdl handle = new TD5*[1];
    handle[0] = new TD5;
    handle[0]->dimSizes[0] = 10;  // Width
    handle[0]->dimSizes[1] = 4;   // Height

    // Fill the elt array with hardcoded values
    for (int i = 0; i < 40; ++i) {
        handle[0]->elt[i] = (i % 2) * 255;  // Alternate between 0 and 255
    }

    return handle;
}

int main() {
    // Create and fill TD1 with hardcoded values
    TD1* td1 = createTD1();
    std::cout << "TD1 created with hardcoded values." << std::endl;

    // Display GlobalRectangle data
    std::cout << "GlobalRectangle Points: ";
    for (int i = 0; i < td1->GlobalRectangle[0]->dimSize; ++i) {
        std::cout << td1->GlobalRectangle[0]->elt[i] << " ";
    }
    std::cout << std::endl;

    // Display Contour data
    for (int i = 0; i < td1->Contours[0]->dimSize; ++i) {
        std::cout << "Contour " << i + 1 << " - ContourType: " << td1->Contours[0]->elt[i].ContourType
                  << ", ROIType: " << td1->Contours[0]->elt[i].ROIType << std::endl;
        std::cout << "Points: ";
        for (int j = 0; j < td1->Contours[0]->elt[i].Points[0]->dimSize; ++j) {
            std::cout << td1->Contours[0]->elt[i].Points[0]->elt[j] << " ";
        }
        std::cout << std::endl;
    }

    // Create and fill TD5 with hardcoded values
    TD5Hdl td5 = createTD5Hdl();
    std::cout << "TD5 created with hardcoded values." << std::endl;

    // Display TD5 data (displaying a subset for brevity)
    std::cout << "TD5 elt data: ";
    for (int i = 0; i < 40; ++i) {
        std::cout << (int)td5[0]->elt[i] << " ";
    }
    std::cout << std::endl;

    // Cleanup: Free allocated memory
    delete[] td1->GlobalRectangle[0];
    for (int i = 0; i < td1->Contours[0]->dimSize; ++i) {
        delete[] td1->Contours[0]->elt[i].Points[0];
    }
    delete[] td1->Contours[0];
    delete td1;
    delete[] td5[0];
    delete[] td5;

    return 0;
}

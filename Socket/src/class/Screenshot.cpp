#include"Screenshot.h"
const int BUFFER_SIZE = 1024;
using namespace std;

std::vector<unsigned char> stringToBytes(std::string str) {
    std::vector<unsigned char> bytes;
    
    for (char c : str) {
        bytes.push_back(c); 
    }
    
    return bytes;
}   

std::string intToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

bool SaveScreenShotToFile(SocketClient s, const char* filename) {
    // Nhan kich thuoc file
    // streampos file_size;
    std::string message = "";
    int start = time(NULL);

    while (difftime(time(NULL), start) < 60)
    {
        message = s.ReceiveBytes();
        if(message!="")
        {
            break;
        }
    }
    // Tao file anh
    if(message=="")
    {
        std::cout << "not received in time";
        return false;
    }
    int file_size;
    istringstream(message) >> file_size;

    ofstream out(filename, ios::binary);
    // char* buffer = new char[BUFFER_SIZE];

    // Nhan file anh
    std::cout << "Waiting for Img...";
    std::string imgs_bytes="";
    while(true)
    {
        imgs_bytes = s.ReceiveBytes();   
        if(imgs_bytes != "")
        {
            std::cout << "Received...";
            break;
        }
    }
    vector<unsigned char> bytes = stringToBytes(imgs_bytes);
    //ghi file
    for (unsigned char b : bytes) {
        out.write((char*)&b, 1);
    }  
    out.close();
    return true;
    // delete[] buffer;
}



void SaveScreenShotToFile(const char* filename) {
    // Lấy handle của màn hình chính
    HDC hScreen = GetDC(NULL);

    // Lấy chiều rộng và chiều cao của màn hình
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Tạo một bitmap với kích thước bằng với màn hình
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);

    // Tạo một DC (device context) mới để vẽ lên bitmap
    HDC hDC = CreateCompatibleDC(hScreen);
    SelectObject(hDC, hBitmap);

    // Sử dụng hàm BitBlt để chụp màn hình vào bitmap
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    // Lưu bitmap vào file
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    BITMAPFILEHEADER bmfHeader = {0};
    bmfHeader.bfType = 0x4D42;
    bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
    bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmp.bmWidth;
    bi.biHeight = bmp.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
    char* pBuffer = new char[bmp.bmWidthBytes * bmp.bmHeight];
    GetDIBits(hDC, hBitmap, 0, bmp.bmHeight, pBuffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    FILE* pFile = fopen(filename, "wb");
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);
    fwrite(pBuffer, bmp.bmWidthBytes * bmp.bmHeight, 1, pFile);
    fclose(pFile);
    delete[] pBuffer;

    // Giải phóng bộ nhớ
    SelectObject(hDC, hOldBitmap);
    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
}


void ScreenShotAndSendToClient(Socket* s,const char* filename) {
    
    SaveScreenShotToFile(filename);
    
    ifstream in(filename, ios::binary | ios::ate);
    streampos file_size = in.tellg();
    in.seekg(0, ios::beg);

    char* buffer = new char[BUFFER_SIZE];
    int bytes_sent = 0;

    // Gui kich thuoc file den server
    s->SendBytes(intToString(sizeof(file_size)));

    // Gui file anh den server
    std::vector<char> bytes;
    
    char c; 
    while(in.read(&c, 1)) {
        bytes.push_back(c);
    }
    std::string img(bytes.begin(), bytes.end());
    s->SendBytes(img);
    in.close();
    delete[] buffer;
}
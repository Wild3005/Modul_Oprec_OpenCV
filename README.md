# Modul_Oprec_OpenCV
> pastikan anda telah menginstall opencv

> cek OpenCV terinstall pada terminal ``` pkg-config --modversion opencv4``` 

> jika sudah buat folder workspace dengan isi didalamnya bernama folder **build**

> (opsional) tambahkan folder src pada workspace untuk menaruh file program

> buat file pada workspace bertuliskan **CMakeLists.txt**

> pada file **CMakeLists.txt** konfigurasikan atau taruh kode seperti dibawah ini:

==============================
cmake_minimum_required(VERSION 3.0)

project( oprec )

find_package( OpenCV REQUIRED )

add_executable( oprec (kode program mu) )

##add_executable( oke1 src/progrobot.cpp )

target_link_libraries( oprec ${OpenCV_LIBS} )

==============================

> jika sudah pada terminal masuk ke direktori folder build

> lalu tuliskan ``` cmake..```

> bila ingin compile code anda harus berada pada direktori build pada terminal lalu gunakan perintah ``` make```

> saat ingin menjalankan anda gunakan perintah ``` ./(nama project yang ada di file txt)```

> pada file txt atau **CMakeLists.txt** tertulis oprec jadi menjadi ``` ./oprec```

> selesai :D
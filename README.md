# Çift Yönlü Bağlantılı Liste Öğrenci Yönetim Sistemi

Bu proje, çift yönlü bağlantılı liste veri yapısını kullanarak bir öğrenci yönetim sistemi uygulamasını gerçekleştirir.

## Özellikler

- Öğrenci ekleme
- Tüm öğrencileri listeleme
- Veri Yapıları dersini alan öğrencileri listeleme
- Öğrencileri isme göre sıralama (A-Z)
- Veri Yapıları ve Algoritma Analizi derslerini alan öğrencileri QuickSort ile numaraya göre sıralama
- Otomatik 25 örnek öğrenci ekleme

## Veri Yapısı

Her öğrenci düğümü şu bilgileri içerir:
- Öğrenci numarası
- TC kimlik numarası
- Ad
- Soyad
- Bölüm
- Aldığı dersler (maksimum 5 ders)
- Önceki ve sonraki düğüm bağlantıları

## Kullanım

Program çalıştırıldığında aşağıdaki menü seçenekleri sunulur:

1. Öğrenci Ekle
2. Tüm Öğrencileri Listele
3. Sadece Veri Yapıları Alanları Listele
4. İsimlere Göre Sırala (A-Z)
5. Veri Yapıları ve Algoritma Analizi Alanları QuickSort (Numaraya Göre)
6. Otomatik 25 Öğrenci Ekle
0. Çıkış

## Derleme ve Çalıştırma

Programı derlemek için:
```bash
gcc cift_baglantili_liste_odev.c -o ogrenci_sistem
```

Çalıştırmak için:
```bash
./ogrenci_sistem
```

## Gereksinimler

- C derleyicisi
- Windows işletim sistemi (windows.h kütüphanesi kullanıldığı için)
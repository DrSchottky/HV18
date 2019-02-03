
"C:\Program Files\ImageMagick-7.0.8-Q16\magick.exe" compare .\orig.png .\fake.png -highlight-color Black -compose src - | "C:\Program Files\ImageMagick-7.0.8-Q16\magick.exe" convert  -negate -background black -alpha off - diff.png

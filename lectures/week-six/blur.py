from PIL import Image, ImageFilter

before = Image.open("tower.bmp")
after = before.filter(ImageFilter.BoxBlur(9))
after.save("out.bmp")

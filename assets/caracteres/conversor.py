from PIL import Image
import os

def save_as_p3(image, filename):
    width, height = image.size
    with open(filename, 'w') as f:
        f.write('P3\n')
        f.write(f'{width} {height}\n')
        f.write('255\n')
        pixels = list(image.getdata())
        for pixel in pixels:
            f.write(f'{pixel[0]} {pixel[1]} {pixel[2]}\n')

def convert_png_to_ppm(directory):
    if not os.path.exists(directory):
        print(f"O diretório {directory} não existe.")
        return

    for filename in os.listdir(directory):
        if filename.endswith(".jpg"):
            filepath = os.path.join(directory, filename)
            with Image.open(filepath) as img:
                img = img.convert("RGBA")
                width, height = img.size
                new_img = Image.new("RGBA", (width, height), "WHITE")  # Cria uma nova imagem com fundo branco
                new_img.paste(img, (0, 0), img)  # Cola a imagem original na nova imagem com fundo branco
                new_img = new_img.convert("RGB")  # Converte para o modo RGB para salvar como PPM
                ppm_filename = os.path.splitext(filepath)[0] + ".ppm"
                save_as_p3(new_img, ppm_filename)
                os.remove(filepath)
                print(f"Convertido {filename} para {os.path.basename(ppm_filename)}")

# Substitua 'caminho/para/sua/pasta' pelo caminho real da pasta que contém suas imagens PNG
convert_png_to_ppm('./')

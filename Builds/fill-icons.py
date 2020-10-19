import sys
import os

icons_map = { 'originals': { 'color': '#375273', 'dir': 'icons/originals/' }, 'nowshed': { 'color': '#4285f4', 'dir': 'icons/nowshed/' } }

def change(icon_set, new_color, output_dir):
    originals_dir = icons_map[icon_set]['dir']
    original_color = icons_map[icon_set]['color']
    
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    for subdir, dirs, files in os.walk(originals_dir):
        for file in files:
            svg_file = os.path.join(subdir, file)
            if not svg_file.endswith(".svg"):
                continue
            print(svg_file)
            new_svg_file = os.path.join(output_dir, file)
            content = open(svg_file, 'rb').read()
            content = content.replace(original_color.encode('utf'), new_color.encode('utf'))
            open(new_svg_file, 'wb').write(content)


if __name__ == "__main__":
    change(sys.argv[1],  sys.argv[2], sys.argv[3])




import cv2
import sys



def printProgress(progress):
    print(f'Progress: |{progress*'#'}{(100-progress)*'-'}| {progress}%', end='\r')
    if progress == 100:
        print('')

def overlap(img, origin_x, origin_y, height, width):
    # Determins overlapping based on the top left and 
    # top right corner of the letter we are inserting.
    return img[origin_y - height][origin_x] == 255 \
           or img[origin_y - height][origin_x + width] == 255 \
           or img[origin_y - height][origin_x] == 0 \
           or img[origin_y - height][origin_x + width] == 0


def insertLetter(origin, letter, img):
    # Inserts letter if it does not overlap and if it fits
    # in the picture.
    origin_x, origin_y = origin
    _, img_width = img.shape
    fontFace = cv2.FONT_HERSHEY_SIMPLEX
    '''fontFaces:
    FONT_HERSHEY_SCRIPT_SIMPLEX
    FONT_HERSHEY_SCRIPT_COMPLEX
    FONT_HERSHEY_COMPLEX_SMALL
    FONT_HERSHEY_TRIPLEX
    FONT_HERSHEY_COMPLEX
    FONT_HERSHEY_DUPLEX
    FONT_HERSHEY_PLAIN
    FONT_HERSHEY_SIMPLEX
    '''
    fontScale = 1
    'change this value to increase the size of inserted letters'

    thickness = 1
    'change this value to increase the thickness of inserted letters'
    
    (txt_width, txt_height), _ = cv2.getTextSize(letter, fontFace, fontScale, thickness)
    if origin_y - txt_height < 0 or origin_x + txt_width >= img_width \
        or overlap(img, origin_x, origin_y, txt_height, txt_width):
        return

    cv2.rectangle(img, origin, (origin_x + txt_width, origin_y - txt_height), 255, thickness=-1)
    cv2.putText(img, letter, origin, fontFace, fontScale, 0, thickness)

progress = 0
printProgress(progress)
img = cv2.imread(sys.argv[1], 0)
img[img != 0] -= 1
img[img == 0] += 1
# We want 0 and 255 to be special values, 
# used to determin overlapping of letters.

for y, row in enumerate(img):
    for x in range(len(row)):
        if row[x] >= 230:
            row[x] = 254
        elif row[x] >= 200:
            insertLetter((x, y), '/', img)
        elif row[x] >= 150:
            insertLetter((x, y), '*', img)
        elif row[x] >= 100:
            insertLetter((x, y), '+', img)
        elif row[x] >= 50:
            insertLetter((x, y), 'M', img)
        elif row[x] >= 0:
            insertLetter((x, y), 'W', img)
        "change letters in '' to choose what letters you want to insert"

    partial_progress = (100*y)//(len(img)-1)
    if partial_progress > progress:
        progress = partial_progress
        printProgress(progress)

img[img != 0] = 255

cv2.namedWindow("ascii_img", cv2.WINDOW_NORMAL)
cv2.imshow("ascii_img", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
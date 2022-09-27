
export class CC {
    private constructor(public readonly code: string) {}

    public static readonly BLACK = new CC('\u001b[30m')
    public static readonly RED = new CC('\u001b[31m')
    public static readonly GREEN = new CC('\u001b[32m')
    public static readonly YELLOW = new CC('\u001b[33m')
    public static readonly BLUE = new CC('\u001b[34m')
    public static readonly MAGENTA = new CC('\u001b[35m')
    public static readonly CYAN = new CC('\u001b[36m')
    public static readonly WHITE = new CC('\u001b[37m')
    public static readonly RESET = new CC('\u001b[0m')
}

let sentence = "";
let previous = CC.RESET

export const print = (value: string, color?: CC) => {
    if (color === undefined) {
        if (previous !== CC.RESET) {
            sentence += CC.RESET.code;
            previous = CC.RESET;
        }
        sentence += value;
        return;
    }
    previous = color;
    sentence += color.code + value;
}

export const println = (value: string, color?: CC) => {
    print(value, color);
    sentence += previous === CC.RESET ? "" : CC.RESET.code;
    previous = CC.RESET;
    console.log(sentence);
    sentence = "";
}


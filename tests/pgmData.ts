

export class PgmData {
    public constructor(
        private readonly pgmType: string,
        private readonly width: number,
        private readonly height: number,
        private readonly max: number,
        private readonly pixels: number[][]
    ) {}

    public static readonly read = async (filename: string): Promise<PgmData> => {
        const output = await Deno.readTextFile(filename)
        const lines = output.split("\n")
        const pgmType = lines[0]
        const [width, height] = lines[1].split(" ").map(Number)
        const max = Number(lines[2])
        const pixels = lines.slice(3)
            .flatMap(line => line.split(" "))
            .filter(value => value === "")
            .map(Number)
            .reduce<number[][]>((chunked, value, i) => {
                if (i % width === 0) return chunked.concat([[value]])
                chunked[Math.trunc(i / width)].push(value)
                return chunked
            }, [])
        return new PgmData(pgmType, width, height, max, pixels)
    }

    public readonly faileReason = (actual: PgmData): string | null => {
        if (actual.pgmType !== "P2") return `PGMタイプ expected: P2, actual: ${actual.pgmType}`
        if (this.height !== actual.height) return `height expected: ${this.height}, actual: ${actual.height}`
        if (this.width !== actual.width) return `width expected: ${this.width}, actual: ${actual.width}`
        if (this.max !== actual.max) return `max value expected: ${this.max}, actual: ${actual.max}`
        if (JSON.stringify(this.pixels) !== JSON.stringify(actual.pixels)) return `中身が異なる`
        return null
    }

}
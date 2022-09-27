import { PgmData } from "./pgmData.ts"

export class CProgramFile {
    public constructor(private readonly filePath: string) {}

    public readonly isExist = async (): Promise<boolean> => {
        try {
            const file = await Deno.stat(this.filePath)
            return file.isFile
        } catch (_e) {
            return false;
        }
    }

    public readonly exec = async (compiler: string, output: string, ...samples: string[]): Promise<PgmData> => {
        await Deno.run({ cmd: [compiler, this.filePath]}).status()
        await Deno.run({ cmd: ["./a.out", ...samples, output]}).status()
        return await PgmData.read(output)
    }
}
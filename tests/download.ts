const baseURL = "https://raw.githubusercontent.com/NITNCtanakaShoki/4I-Summer-Pro3-Asignments/main/src/"

export const download = async (filename: string) => {
    const response = await fetch(baseURL + filename)
    await Deno.writeTextFile(filename, await response.text())
}
const baseURL = "https://raw.githubusercontent.com/NITNCtanakaShoki/4I-Summer-Pro3-Asignments/main/src/"

export const download = async (tests: string[]) => {
    try {
        await Deno.stat("expecteds");
        await Deno.remove("expecteds", { recursive: true })
    } catch (e) {}
    await Deno.mkdir("expecteds")
    await Promise.all(tests.map(async test => {
        const response = await fetch(baseURL + `22-${test}.c`)
        await Deno.writeTextFile(`expecteds/22-${test}.c`, await response.text())
    }))
}

export const downloadSample = async (samples: string[]) => {
    try {
        await Deno.stat("samples");
        await Deno.remove("samples", { recursive: true })
    } catch {}
    await Deno.mkdir("samples")
    const url = "https://raw.githubusercontent.com/NITNCtanakaShoki/4I-Summer-Pro3-Asignments/main/assets/"
    await Promise.all(samples.map(async sample => {
        const response = await fetch(url + sample)
        await Deno.writeTextFile("samples/"+sample, await response.text())
    }))
}
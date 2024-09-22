describe 'compression' do
  def run_script(commands)
    raw_output = nil
    IO.popen('bin/compress', 'r+') do |pipe|
      commands.each do |command|
        pipe.puts command
      end
      pipe.close_write
      raw_output = pipe.gets(nil)
    end
    raw_output.split("\n")
  end
  it 'hello world' do
    result = run_script([''])
    expect(result).to eq(['hello world'])
  end
end
